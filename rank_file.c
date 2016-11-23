#include "rank_file.h"

int WriteRanklist(Rank * psrRanks, const int nSize)
{
	FILE* pfRanklist = NULL;
	int nIndex = 0;
	int err;

	// 打开文件
	err = fopen_s(&pfRanklist,"Ranklist.dat", "wb");

	// 打开文件出错
	if (err != 0)
	{
		printf("文件打开失败！");
		getchar();
		return FALSE;
	}

	// 写入排名的总数
	fprintf(pfRanklist, "TOTALCOUNT%d RANKLIST\n", nSize);

	// 遍历Rank结构体数组，逐行显示
	for (nIndex = 0; nIndex < nSize; nIndex++)
	{
		psrRanks = &psrRanks[nIndex];

		// 写文件，字段之间使用“=>”分隔
		fprintf(pfRanklist, "%s=>%d\n", psrRanks->name, psrRanks->step);
	}

	// 关闭文件
	fclose(pfRanklist);

	return TRUE;
}

int ReadRanklist(Rank* psrRanks, const int nMaxSize)
{
	FILE* pfRanklist = NULL;		// 排行榜文件指针
	int nSize = 0;					// 排名玩家个数
	int nIndex = 0;					// 数组的索引号
	char acBuf[128];				// 用来保存从文件中读取上来的数据
	int err;

	// 打开文件，fopen_s第一个参数为指向文件的指针名，第二个参数为文件名，第三个参数为打开方式
	err = fopen_s(&pfRanklist, "Ranklist.dat", "r");

	// 打开文件出错
	if (err != 0)
	{
		printf("文件打开失败！");
		getchar();
		return FALSE;
	}

	// 读取排名信息的个数
	fscanf_s(pfRanklist, "TOTALCOUNT%d RANKLIST\n", &nSize);

	// 逐行读取文件，如果文件超出10条，或读取到文件尾，都结束读取
	for (nIndex = 0; (nIndex < nSize && nIndex < nMaxSize) || !feof(pfRanklist); )
	{
		// 读取一行记录，在格式化中要标上\n，这样读取的就是一行记录
		fscanf_s(pfRanklist, "%s\n", &acBuf, 128);

		// 也可以不通过解析函数
		// fscanf_s(pfRanklist, "%s => %d\n", &srRank.name,&srRank.step); 

		if (strlen(acBuf) > 0)
		{
			psrRanks[nIndex] = ParseRank(acBuf);		// 解析排名信息，排名信息以=> 分隔
			nIndex++;									// 读取成功一行才进行下一次
		}
	}

	// 关闭文件
	fclose(pfRanklist);

	// 返回数据个数 
	return nSize;
}

Rank ParseRank(char * pcBuf)
{
	const char * DELIMS = "=>";		// 字符串中的分割符
	char *pcTmp = NULL;				// 字符指针用来接收strtok函数的返回值，指向分隔出来的字符串的地址
	char *next_token = NULL;        //保存缓冲块中下一个将被读取的位置
	Rank srRank;

	// 解析姓名
	pcTmp = strtok_s(pcBuf, DELIMS, &next_token);
	if (pcTmp != NULL)
	{
		strcpy_s(srRank.name,sizeof(srRank.name), pcTmp);
	}

	// 解析落子步数
	pcTmp = strtok_s(NULL, DELIMS, &next_token);
	if (pcTmp != NULL)
	{
		srRank.step = atoi(pcTmp);	// 将字符串转换成整型数
	}

	return srRank;
}