#include <iostream>
#include "aho_corasick.hpp"

using namespace std;
using namespace aho_corasick;

int main()
{
	trie t;
	t.insert("hello");
	t.insert("abcde");
	t.insert("word");
	t.insert("aaackd");
	t.insert("aaackd");
	t.insert("wordbb");
	t.insert("wordaa");
	t.case_insensitive();

	auto m_emits = t.parse_text("this is a word and word");
	for (auto m_emit : m_emits)
	{
		cout << m_emit.get_keyword() << endl;
		cout << m_emit.get_start() << ", " << m_emit.get_end() << endl;
		cout << m_emit.size() << endl;
	}
}
