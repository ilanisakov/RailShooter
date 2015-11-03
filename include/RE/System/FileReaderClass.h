/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __FILEREADERCLASS_H_
#define __FILEREADERCLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL FileReaderClass
{
	SystemSingleton* m_pSystem = nullptr; //System pointer
	FILE* m_pFile; //File pointer
	std::ifstream m_iStream;
	std::ofstream m_oStream;

public:
	String m_sLine = ""; //Line of file
	String m_sFirstWord = "";

	/* constructor */
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	FileReaderClass(void);
	/* Copy constructor */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	FileReaderClass(const FileReaderClass& other);
	/* Copy assignment operator */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	FileReaderClass& operator=(const FileReaderClass& other);
	/* Destructor */
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	~FileReaderClass(void);
	
	/* Deallocate object from memory */
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);

	/* Rewinds the file */
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Rewind(void) const;

	/* Reads Files and allocates it on the string */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS ReadFile(String a_sFileName);

	/* Saves a file with the specified name and location */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS SaveFile(String a_sFileName);

	/* Saves a file in binary mode */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS SaveBinaryFile(String a_sFileName);

	/* Reads Binary Files */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS ReadBinaryFile(String a_sFileName);

	/* closes the file */
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void CloseFile(void);

	/* writes a line of the file and saves it in the string */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS WriteLine(String a_sStringInput);

	/* writes a line of the file and saves it in the char array */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS WriteLine(const char * _Format, ...);
	
	/* writes on the same line of the file and saves it in the string */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS Write(String a_sStringInput);

	/* writes on the same line of the file and saves it in the char array */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS Write(const char * _Format, ...);

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void WriteInt(int input);

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void WriteFloat(float input);

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void WriteBool(bool input);

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void WriteString(String input);


	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int ReadInt(void);

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	float ReadFloat(void);

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	bool ReadBool(void);

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	String ReadString(void);

	/* Removes all tabs from the string (it makes regular spaces)*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS RemoveTabs(String* a_sInput);

	/* reads a line of the file and saves it in the string */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS ReadNextLine(bool a_bSkipComments = true);
	/* 
	Removes the blank spaces of the line
		Modified by AndrewWilkinson88@gmail.com
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS RemoveBlanks(char** a_szInput);

	/*Removes the blank spaces of the line and returns a new copy*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS RemoveBlanks(char* a_szInput);

	/*Removes the blank spaces of the line and returns a new copy*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	REERRORS RemoveBlanks(String* a_sInput);

	/* Gets the first word of the line */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	String GetFirstWord(bool a_bToUpper = false);

	/*Gets a file name from a explorer window*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	String RetriveFileNameFromExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;

	/*Tells a file name from explorer window*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	String IndicateFileNameOnExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;

	/*Gets the filename with extension from the name */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	static String GetFileNameAndExtension(String a_sFileName);

	/*Gets the filename from the name */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	static String GetFileName(String a_sFileName);

	/*Gets the extension from the filename*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	static String GetExtension(String a_sFileName);

	/* Gets the absolute route from a file name */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	static String GetAbsoluteRoute(String a_sFileName);

	/* Returns the string in uppercase */
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	static String ToUpper(String a_sInput);

private:
	/* Initializates the variables of the object*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<FileReaderClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<FileReaderClass*>;

}
#endif //_EMPTY_H
