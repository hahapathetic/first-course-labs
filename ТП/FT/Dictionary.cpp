#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "IOfmtGuard.h"
#include "CommonCommands.h"

void Dictionary::showKeys(std::wostream& out)
{
  iofmtguard guard(out);
  for (auto it = table_.begin(); it != table_.end(); ++it)
  {
    out << it->first << ";\n";
  }
}

void Dictionary::showAll(std::wostream& out)
{
  iofmtguard guard(out);
  if (!table_.empty())
  {
    for (auto it = table_.begin(); it != table_.end(); ++it)
    {
      out << it->first << ": ";
      std::copy(it->second.begin(), it->second.end(), std::ostream_iterator< std::wstring, wchar_t >(out, L";\n"));
    }
  }
  else
  {
    out << "Dictionary is empty.\n";
  }
}

void Dictionary::showWordTranslation(std::wostream& out, const std::wstring key)
{
  auto it = table_.find(key);
  if (it != table_.end())
  {
    std::copy(it->second.begin(), it->second.end(), std::ostream_iterator< std::wstring, wchar_t >(out, L";\n"));
  }
  else
  {
    out << "Word not found.\n" << std::endl;
  }
}

void Dictionary::addWord(std::wstring& key, std::wstring& value)
{
  if (isWord(key) && isSentence(value))
  {
    table_[key].push_back(value);
    std::sort(table_[key].begin(), table_[key].end(), std::less< std::wstring >());
  }
  else
  {
    throw std::invalid_argument("INVALID ARGUMENTS");
  }
}

void Dictionary::addKey(std::wstring& key)
{
  if (search(key) != true)
  {
    if (isWord(key))
    {
      table_[key] = std::vector< std::wstring >();
    }
    else
    {
      throw std::invalid_argument("INVALID ARGUMENTS");
    }
  }
  else
  {
    throw std::invalid_argument("SUCH WORD ALREADY EXISTS");
  }
}

void Dictionary::deleteWord(std::wstring key)
{
  if (table_.find(key) != table_.end())
    table_.erase(key);
}

void Dictionary::deleteTranslation(std::wstring key, std::wstring value)
{
  if (table_.find(key) != table_.end())
  {
    std::vector< std::wstring >::iterator it = std::find(table_[key].begin(), table_[key].end(), value);
    if (it != table_[key].end())
    {
      table_[key].erase(it);
    }
  }
}

bool Dictionary::search(std::wstring key)
{
  return ((table_.find(key) != table_.end() ? true : false));
}

void Dictionary::deleteDict()
{
  table_.clear();
}

Dictionary Dictionary::merge(const Dictionary& dict)
{
  Dictionary mergedDict = *this;
  for (auto it = dict.table_.begin(); it != dict.table_.end(); ++it)
  {
    if (table_.find(it->first) != table_.end())
    {
      if (table_[it->first] != it->second)
      {
        std::vector< std::wstring > dest;
        std::set_union(table_[it->first].begin(), table_[it->first].end(),
          it->second.begin(), it->second.end(), std::back_inserter(dest));
        sort(dest.begin(), dest.end(), std::less< std::wstring >());
        mergedDict.table_[it->first] = dest;
      }
    }
    else
    {
      mergedDict.table_.insert(std::make_pair(it->first, it->second));
    }
  }
  return mergedDict;
}

Dictionary mergeDictionaries(const Dictionary& dict, const Dictionary& yaDict)
{
  Dictionary uniqueDict;
  for (auto it = dict.table_.begin(); it != dict.table_.end(); ++it)
  {
    if (yaDict.table_.find(it->first) == yaDict.table_.end())
    {
      uniqueDict.table_.insert(std::make_pair(it->first, it->second));
    }
  }
  for (auto it = yaDict.table_.begin(); it != yaDict.table_.end(); ++it)
  {
    if (dict.table_.find(it->first) == dict.table_.end())
    {
      uniqueDict.table_.insert(std::make_pair(it->first, it->second));
    }
  }
  return uniqueDict;
}
