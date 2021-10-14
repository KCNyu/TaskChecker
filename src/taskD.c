#include "taskD.h"
#include "variable.h"

const char *DTaskInfoRussian[] = {
    "Написать программу shellD1, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN ; cmdB B1 B2 … BM\nЭта конструкция обеспечивает последовательное выполнение команд cmdA и cmdB:вначале запускается команда cmdA с параметрами A1, A2, …, AN, затем запускается команда cmdB с параметрами B1, B2, …, BM. Каждая команда использует стандартный вывод на экран.\nФормат вызова программы shellD1:\nshellD1 cmdA N A1 A2 … AN cmdB M B1 B2 … BM\n"};
const char *DTaskInfoChinese[] = {
    "一\n"};
const char *c1[] = {"ls", "1", "-r"};
const char *c2[] = {"df", "2", "-P", "-h"};
const char *c3[] = {"cat", "1", "/etc/passwd"};
const char *c4[] = {"date", "3", "-d", "-1day", "+%Y-%m-%d"};
const char **DTaskTestCmd[] = {c1, c2, c3, c4};
void dataD(char *filename, int *nargs, int tasknum, int testnum)
{
	for (int i = 0; i < 8; i++)
		filename[i] = (char)(rand() % 26 + 97);
	filename[8] = '\0';
	strcat(filename, testfileext);
	int f = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(f);
	// rand args
	int A = rand() % 4, B = rand() % 4;
	const char **cmd1 = DTaskTestCmd[A], **cmd2 = DTaskTestCmd[B];
	int size_cmd1 = 2 + atoi(cmd1[1]);
	int size_cmd2 = 2 + atoi(cmd2[1]);
	*nargs = size_cmd1 + size_cmd2 + 1;
	char sys_cmd[100];
	for (int i = 1; i < *nargs; i++)
	{
		args[i] = (char *)malloc(50);
		if (i <= size_cmd1)
		{
			strcpy(args[i], cmd1[i - 1]);
			if (i != 2)
			{
				strcat(sys_cmd, args[i]);
				strcat(sys_cmd," ");
				if (i == size_cmd1)
					strcat(sys_cmd,";");
			}
		}
		else
		{
			strcpy(args[i], cmd2[i - size_cmd1 - 1]);
			if (i != size_cmd1+2)
			{
				strcat(sys_cmd, args[i]);
				strcat(sys_cmd," ");
			}
		}
	}
	// end
	f = open(controlfilename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	int backup = dup(STDOUT_FILENO);
	dup2(f, STDOUT_FILENO);
	close(f);
	switch (tasknum)
	{
	case 1:
		system(sys_cmd);
		break;
	default:
		break;
	}
	dup2(backup, STDOUT_FILENO);
}