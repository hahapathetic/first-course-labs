#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <unordered_map>
#include <vector>
#include <list>
#include <string>


class Dictionary
{
public:
  Dictionary() = default;
  ~Dictionary() = default;
  void showKeys(std::wostream& out);
  void showAll(std::wostream& out);
  void showWordTranslation(std::wostream& out, const std::wstring key);
  void addWord(std::wstring& key, std::wstring& value);
  void addKey(std::wstring& key);
  void deleteWord(std::wstring key);
  void deleteTranslation(std::wstring key, std::wstring value);
  bool search(std::wstring key);
  void deleteDict();
  Dictionary merge(const Dictionary& dict);
  friend Dictionary mergeDictionaries(const Dictionary& dict1, const Dictionary& dict2);
private:
  std::unordered_map< std::wstring, std::vector< std::wstring > > table_;
};

#endif
