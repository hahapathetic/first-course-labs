#include "Commands.h"
#include <iostream>
#include <fstream>
#include <regex>
#include "IOfmtGuard.h"
#include "CommonCommands.h"

Commands::Commands(std::wostream& out, std::wistream& in, Dictionary& dict):
  out_(out),
  in_(in),
  dict_(dict)
{}

void Commands::help()
{
  iofmtguard guard(out_);
  if (in_.peek() == '\n')
  {
    out_ << "Available commands:\n" <<
      "HELP - output a list of commands for interacting with the dictionary\n" <<
      "SHOW KEYS - output of all English words in the dictionary to the console\n" <<
      "SHOW ALL - output of all words in the dictionary with their translations\n" <<
      "ADD WORD - adding a word to the dictionary\n" <<
      "ADD TRANSLATION - adding a word translation to the dictionary\n" <<
      "DELETE WORD - deleting a word from the dictionary\n" <<
      "DELETE TRANSLATION - deleting a translation of a word from the dictionary\n" <<
      "DELETE ALL - deleting the entire dictionary\n" <<
      "MERGE <fileName1> — creating a new dictionary(fileName3)" <<
      "from the contents of two other dictionaries(fileName1, fileName2)\n" <<
      "MERGE UNIQUE <fileName1> <fileName2> <fileName3> - creating a new dictionary(fileName3)" <<
      "from unique words in two other dictionaries(fileName1, fileName2)\n";
  }
  else
  {
    getInvalidMessage(in_, out_);
  }
}

void Commands::show()
{
  iofmtguard guard(out_);
  char c = in_.get();
  in_.putback(c);
  if (c == '\n')
  {
    getInvalidMessage(in_, out_);
  }
  else
  {
    std::wstring option = L"";
    in_ >> option;
    if (option == L"TRANSLATION")
    {
      std::wstring word = L"";
      in_ >> word;
      if (isWord(word))
      {
        dict_.showWordTranslation(out_, word);
      }
      else
      {
        getInvalidMessage(in_, out_);
      }
    }
    else if (option == L"KEYS")
    {
      dict_.showKeys(out_);
    }
    else if (option == L"ALL")
    {
      dict_.showAll(out_);
    }
    else
    {
      getInvalidMessage(in_, out_);
    }
  }
}

void Commands::add()
{
  iofmtguard guard(out_);
  std::wstring option = L"";
  in_ >> option;
  std::wstring word = L"";
  std::wstring translation = L"";
  in_ >> word;
  if (option == L"TRANSLATION")
  {
    std::getline(in_ >> std::ws, translation, L'\n');
    if (in_)
    {
      try
      {
        dict_.addWord(word, translation);
      }
      catch (const std::exception& e)
      {
        out_ << e.what() << "\n";
      }
    }
    else
    {
      getInvalidMessage(in_, out_);
    }
  }
  else if (option == L"WORD")
  {
    if (in_)
    {
      try
      {
        dict_.addKey(word);
      }
      catch (const std::exception& e)
      {
        out_ << e.what() << "\n";
      }
    }
    else
    {
      getInvalidMessage(in_, out_);
    }
  }
  else
  {
    getInvalidMessage(in_, out_);
  }
}

void Commands::remove()
{
  iofmtguard guard(out_);
  std::wstring option = L"";
  in_ >> option;
  if (option == L"WORD")
  {
    std::wstring word = L"";
    in_ >> word;
    if (isWord(word))
    {
      dict_.deleteWord(word);
    }
    else
    {
      getInvalidMessage(in_, out_);
    }
  }
  else if (option == L"TRANSLATION")
  {
    std::wstring word = L"";
    std::wstring translation = L"";
    in_ >> word;
    char c = in_.get();
    in_.putback(c);
    if (c != '\n' && isWord(word))
    {
      std::getline(in_ >> std::ws, translation, L'\n');
      if (in_ && isSentence(translation))
      {
        dict_.deleteTranslation(word, translation);
      }
      else
      {
        getInvalidMessage(in_, out_);
      }
    }
    else
    {
      getInvalidMessage(in_, out_);
    }
  }
  else if (option == L"ALL")
  {
    dict_.deleteDict();
  }
  else
  {
    getInvalidMessage(in_, out_);
  }
}

void Commands::merge()
{
  iofmtguard guard(out_);
  char c = in_.get();
  in_.putback(c);
  Dictionary fileDict;
  std::wstring word = L"";
  std::wstring translation = L"";
  std::wifstream fileIn;
  out_ << "Enter file:\n";
  std::wstring fileName = L"";
  in_ >> fileName;
  fileIn.open(fileName);
  while (!fileIn)
  {
    out_ << "Something wrong with file. Try again.\n";
    in_ >> fileName;
    fileIn.open(fileName);
  }
  readFile(fileName, fileDict);
  fileIn.close();
  Dictionary doneDict = dict_.merge(fileDict);
  out_ << "Enter the name of the file you want to output the result to: \n";
  std::wstring outFile;
  in_ >> outFile;
  std::wofstream output;
  output.open(outFile);
  doneDict.showAll(output);
}

void Commands::mergeUnique()
{
  iofmtguard guard(out_);
  char c = in_.get();
  in_.putback(c);
  Dictionary fileDict;
  std::wstring word = L"";
  std::wstring translation = L"";
  std::wifstream fileIn;
  out_ << "Enter file 1:\n";
  std::wstring fileName = L"";
  in_ >> fileName;
  fileIn.open(fileName);
  while (!fileIn)
  {
    out_ << "Something wrong with file 1. Try again.\n";
    in_ >> fileName;
    fileIn.open(fileName);
  }
  readFile(fileName, fileDict);
  fileIn.close();

  Dictionary yaFileDict;
  std::wifstream yaFileIn;
  out_ << "Enter file 2:\n";
  std::wstring yaFileName = L"";
  in_ >> yaFileName;
  yaFileIn.open(yaFileName);
  while (!yaFileIn)
  {
    out_ << "Something wrong with file 2. Try again.\n";
    in_ >> yaFileName;
    fileIn.open(yaFileName);
  }
  readFile(yaFileName, yaFileDict);
  yaFileIn.close();
  Dictionary doneDict = mergeDictionaries(fileDict, yaFileDict);
  out_ << "Enter the name of the file you want to output the result to: \n";
  std::wstring outFile;
  in_ >> outFile;
  std::wofstream output;
  output.open(outFile);
  doneDict.showAll(output);
}
