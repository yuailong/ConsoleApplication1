#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <iostream>
#include <tlhelp32.h>

using namespace std;

//读取64位的PE文件的信息
class PEStruct{
public:
	PEStruct(const char* filePath);
	~PEStruct();
	void printNTHeaders();
	void printTables();
	void printExportTable();
	void printImportTable();
	void printImportFunc(PIMAGE_THUNK_DATA RVA_INT, size_t numPrint);
	void printRelocTable();//打印重定位表
private:
	FILE* file = NULL;
	UINT64 fileBuffer = NULL;
	char* filePath = NULL;
	PIMAGE_DOS_HEADER pDosHeader = NULL;//DOS头
	char* pDosStub = NULL;
	IMAGE_NT_HEADERS64* pNTHeader = NULL;//NT头
	PIMAGE_FILE_HEADER pPEHeader = NULL;//PE头
	PIMAGE_OPTIONAL_HEADER64 pOptionHeader = NULL;//扩展PE头
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;//节头

	/*
	* 各种表
	*/
	PIMAGE_EXPORT_DIRECTORY pExportTable = NULL;//导出表FOA
	UINT64   FOA_AddressOfFunctions;     // 导出函数地址FOA
	UINT64   FOA_AddressOfNames;         // 导出函数名字表FOA
	UINT64   FOA_AddressOfNameOrdinals;  // 导出函数序号表FOA         
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = NULL;//导入表FOA
	PIMAGE_BASE_RELOCATION pRelocTable = NULL;//导入表FOA
	size_t numOfImportTable = 0;//导入表的数量
	size_t numOfRelocTable = 0;//重定位表的数量

	//根据RVA获取FOA
	UINT64 getFOA(UINT64 RVA);

	bool ReadPEFile();

	void getPEInformation();//获取PE的所有信息
	void getHeadersInfomation();//获取各种头的信息
	void getExportTableInformation();//获取导出表信息
	void getImportTableInformation();//获取导入位表信息
	void getRelocTableInformation();//获取重定位表信息
	size_t getNumOfFunc(PIMAGE_THUNK_DATA RVA_INT);
};

int main(){
	//读取PE文件信息
	PEStruct* pPE = new PEStruct("生成动态链接库.dll");
	pPE->printNTHeaders();
	pPE->printTables();
	delete pPE;
	return 0;
}

PEStruct::PEStruct(const char* filePath){
	this->filePath = (char*)filePath;
	ReadPEFile();
	getPEInformation();
}

PEStruct::~PEStruct(){
	if(file){
		fclose(file);
	}
	if(fileBuffer){
		free((void*)fileBuffer);
		fileBuffer = NULL;
	}
}

//根据RVA获取FOA
UINT64 PEStruct::getFOA(UINT64 RVA){
	if(pOptionHeader->FileAlignment == pOptionHeader->SectionAlignment){
		return RVA;
	}
	else if(RVA >= (UINT64)pDosHeader &&
			RVA < (UINT64)pDosHeader + pOptionHeader->SizeOfHeaders){
		return RVA;
	}
	else{
		for(size_t i = 0; i < pPEHeader->NumberOfSections; i++){
			IMAGE_SECTION_HEADER sh = pSectionHeader[i];
			UINT64 sizeOfSection = sh.Misc.VirtualSize > sh.SizeOfRawData ? sh.Misc.VirtualSize : sh.SizeOfRawData;
			UINT64 sizeOfSectionAligned = (UINT64)ceil((double)sizeOfSection / pOptionHeader->SectionAlignment) * pOptionHeader->SectionAlignment;
			if(RVA >= pSectionHeader[i].VirtualAddress &&
			   RVA < pSectionHeader[i].VirtualAddress + sizeOfSectionAligned){
				return RVA - sh.VirtualAddress + sh.PointerToRawData;
			}
		}
	}
	return 0x0;
}

bool PEStruct::ReadPEFile(){
	if(filePath == NULL){
		return false;
	}

	//打开文件	
	fopen_s(&file, filePath, "rb");
	if(!file){
		printf(" 无法打开文件:%s", filePath);
		return false;
	}
	//读取文件大小		
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	//分配缓冲区	
	fileBuffer = (UINT64)malloc(fileSize);

	if(!fileBuffer){
		printf(" 分配空间失败! ");
		fclose(file);
		return false;
	}

	//将文件数据读取到缓冲区	
	size_t n = fread((void*)fileBuffer, fileSize, 1, file);
	/*
	if(!n){
		printf(" 读取数据失败! ");
		free((void*)fileBuffer);
		fclose(file);
		return false;
	}
	*/

	//关闭文件	
	fclose(file);
	return true;
}

void PEStruct::getHeadersInfomation(){
	//各种头
	pDosHeader = (PIMAGE_DOS_HEADER)fileBuffer;
	pDosStub = (char*)(pDosHeader + 1);
	pNTHeader = (PIMAGE_NT_HEADERS)((UINT64)fileBuffer + pDosHeader->e_lfanew);
	pPEHeader = &(pNTHeader->FileHeader);
	pOptionHeader = &(pNTHeader->OptionalHeader);
	pSectionHeader = (PIMAGE_SECTION_HEADER)(pNTHeader + 1);
}

void PEStruct::getPEInformation(){
	getHeadersInfomation();
	//各种表
	getExportTableInformation();
	getImportTableInformation();
	getRelocTableInformation();
}

void PEStruct::getExportTableInformation(){
	IMAGE_DATA_DIRECTORY dd = pOptionHeader->DataDirectory[0];
	DWORD RVA_exportTable = dd.VirtualAddress;//导出表的RVA（相对虚拟地址）
	if(RVA_exportTable != 0){
		UINT64 FOA_exportTable = getFOA(RVA_exportTable);
		pExportTable = (PIMAGE_EXPORT_DIRECTORY)(FOA_exportTable + fileBuffer);
		//导出表的3个子表
		DWORD nameTabel = pExportTable->AddressOfNames;//函数名称地址表的RVA
		DWORD ordinalsTable = pExportTable->AddressOfNameOrdinals;//函数序号表的RVA
		DWORD addressTable = pExportTable->AddressOfFunctions;//函数地址表的RVA
	}
}

void PEStruct::getImportTableInformation(){
	IMAGE_DATA_DIRECTORY dd1 = pOptionHeader->DataDirectory[1];
	DWORD RVA_importTable = dd1.VirtualAddress;//导入表的RVA（相对虚拟地址）
	if(RVA_importTable == 0x0){//如果RVA是0，表示没有导入表
		return;
	}
	UINT64 FOA_importTable = getFOA(RVA_importTable);//导入表FOA
	pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)(FOA_importTable + fileBuffer);

	/*
	计算有几个导入表，
	结构体IMAGE_IMPORT_DESCRIPTOR的大小是20个字节，最后一个导入表的后面的20个字节都是0
	*/
	numOfImportTable = 0;
	PIMAGE_IMPORT_DESCRIPTOR addressOfImportTable = pImportTable;
	while(!(addressOfImportTable->OriginalFirstThunk == 0 &&
		  addressOfImportTable->TimeDateStamp == 0 &&
		  addressOfImportTable->ForwarderChain == 0 &&
		  addressOfImportTable->Name == 0 &&
		  addressOfImportTable->FirstThunk == 0)){
		addressOfImportTable++;
		numOfImportTable++;
	}
}

void PEStruct::getRelocTableInformation(){
	IMAGE_DATA_DIRECTORY dd1 = pOptionHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
	UINT64 RVA_relocTable = dd1.VirtualAddress;//重定位表的RVA（相对虚拟地址）
	if(RVA_relocTable == 0x0){//如果RVA是0，表示没有重定位表
		return;
	}
	UINT64 FOA_relocTable = getFOA(RVA_relocTable);//重定位表FOA
	pRelocTable = (PIMAGE_BASE_RELOCATION)(FOA_relocTable + fileBuffer);

	/*
	计算重定位表的个数
	*/

}

void PEStruct::printNTHeaders(){
	//打印DOS头	
	printf("* DOS头：\n");
	char mzStr[3];
	mzStr[0] = ((char*)pDosHeader)[0];
	mzStr[1] = ((char*)pDosHeader)[1];
	mzStr[2] = '\0';
	printf("MZ标志：0x%X（%s）\n", pDosHeader->e_magic, mzStr);
	printf("PE偏移：0x%X\n----------------------------------------\n", pDosHeader->e_lfanew);

	//打印NT头	
	printf("* NT头：\n");
	char peStr[5];
	peStr[0] = ((char*)pNTHeader)[0];
	peStr[1] = ((char*)pNTHeader)[1];
	peStr[2] = ((char*)pNTHeader)[2];
	peStr[3] = ((char*)pNTHeader)[3];
	peStr[4] = '\0';
	printf("PE标志：0x%08X（%s）\n----------------------------------------\n", pNTHeader->Signature, peStr);

	//PE头
	printf("* PE头：\n");
	printf("pPEHeader->Machine :0x%X (表示程序可以运行在什么CPU上  0x0：任意CPU  0x14C：Intel386及以后的CPU  0x8664：x64的CPU)\n", pPEHeader->Machine);
	printf("节的数量：%x\n", pPEHeader->NumberOfSections);
	printf("扩展PE头的大小：0x%X\n----------------------------------------\n", pPEHeader->SizeOfOptionalHeader);

	//扩展PE头	
	printf("* 扩展PE头：\n");
	cout << "内存对齐:" << pOptionHeader->SectionAlignment << endl;
	cout << "文件对齐:" << pOptionHeader->FileAlignment << endl;
	printf("Magic：0x%X (表示程序是32位或者64位的，   0x10B：32位    0x20B：64位)\n----------------------------------------\n", pOptionHeader->Magic);
}

void PEStruct::printTables(){
	this->printExportTable();
	this->printImportTable();
	this->printRelocTable();
}

void PEStruct::printExportTable(){
	printf("* 导出表：\n");
	if(!pExportTable){
		printf("没有导出表\n----------------------------------------\n");
		return;
	}
	printf("导出函数名：\n");
	DWORD RVA_Names = pExportTable->AddressOfNames;
	DWORD* pNames = (DWORD*)(getFOA(RVA_Names) + fileBuffer);
	DWORD RVA_Ordinals = pExportTable->AddressOfNameOrdinals;
	WORD* pOdinals = (WORD*)(getFOA(RVA_Ordinals) + fileBuffer);
	DWORD RVA_funAddr = pExportTable->AddressOfFunctions;
	DWORD* pAddr = (DWORD*)(getFOA(RVA_funAddr) + fileBuffer);

	printf("有%d个以名字导出的函数:\n", pExportTable->NumberOfNames);
	for(unsigned int i = 0; i < pExportTable->NumberOfNames; i++){
		DWORD RVA_name = *(pNames++);
		char* FOA_name = (char*)(getFOA(RVA_name) + fileBuffer);
		printf("(%d) 序号：%X, 地址：%X, 函数名字：%s\n", i, pOdinals[i], pAddr[pOdinals[i]], FOA_name);
		if(i >= 10){
			printf("...\n");
			break;
		}
	}
	printf("\n----------------------------------------\n");
}

//获取导入表对应的模块名
void PEStruct::printImportTable(){
	printf("* 导入表：\n");
	cout << "有" << numOfImportTable << "个导入表：" << endl;
	for(size_t i = 0; i < numOfImportTable; i++){
		IMAGE_IMPORT_DESCRIPTOR importTable = pImportTable[i];//导入表
		char* nameOfTable = (char*)(getFOA(pImportTable[i].Name) + fileBuffer);//导入表对应的模块名字
		//INT表
		UINT64 RVA_INT = importTable.OriginalFirstThunk;
		UINT64 FOA_INT = getFOA((UINT64)RVA_INT);
		PIMAGE_THUNK_DATA pINT = (PIMAGE_THUNK_DATA)(FOA_INT + fileBuffer);

		//计算这个导入表有几个函数
		size_t numOfFunc = getNumOfFunc(pINT);

		//打印
		printf("第%I64u个导入表，模块名字：%s，OriginalFirstThunk：0x%08X\n    有%I64u个函数：\n", i + 1, nameOfTable, importTable.OriginalFirstThunk, numOfFunc);

		//打印函数，最多打印3个好了
		this->printImportFunc(pINT, numOfFunc < 3 ? numOfFunc : 3);
	}
	printf("\n----------------------------------------\n");
}

//计算有多少个函数
size_t PEStruct::getNumOfFunc(PIMAGE_THUNK_DATA pINT){
	size_t num = 0;
	while(pINT[num].u1.AddressOfData != 0){
		num++;
	}
	return num;
}

//获取函数名字、序号
void PEStruct::printImportFunc(PIMAGE_THUNK_DATA pINT, size_t numPrint){
	for(size_t i = 0; i < numPrint; i++){
		IMAGE_THUNK_DATA INT = pINT[i];
		UINT64 forwarderString = INT.u1.ForwarderString;
		//判断函数是用序号还是名字导出的
		bool isOridinalExport = forwarderString >> 31 == 1 ? true : false;
		printf("    第%I64u个函数，序号：0x%I64u", i + 1, INT.u1.Ordinal);
		if(isOridinalExport){
			cout << "，无函数名" << endl;
		}
		else{
			UINT64 RVA_name = INT.u1.AddressOfData;
			UINT64 FOA_name = getFOA(RVA_name);
			PIMAGE_IMPORT_BY_NAME pName = (PIMAGE_IMPORT_BY_NAME)(FOA_name + fileBuffer);
			char* name = (char*)(pName->Name);
			cout << "，函数名：" << name << endl;
		}
	}
	printf("    ......\n\n");
}

void PEStruct::printRelocTable(){

}