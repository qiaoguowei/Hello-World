#ifndef _INTERVAL_H
#define _INTERVAL_H

#include <iostream>

class interval
{
	size_t d_start;
	size_t d_end;

public:
	interval(size_t start, size_t end) : d_start(start), d_end(end) {}

	size_t get_start() const
	{
		return d_start;
	}

	size_t get_end() const
	{
		return d_end;
	}

	size_t size() const
	{
		return d_end - d_start + 1;
	}

	bool overlaps_with(const interval& other) const
	{
		return d_start <= other.d_end && d_end >= other.d_start;
	}

	bool overlaps_with(size_t point) const
	{
		return d_start <= point && point <= d_end;
	}

	bool operator < (const interval& other) const
	{
		return get_start() < other.get_start();
	}

	bool operator != (const interval& other) const
	{
		return get_start() != other.get_start() || get_end() != other.get_end();
	}

	bool operator == (const interval& other) const
	{
		return get_start() == other.get_start() && get_end() == other.get_end();
	}
};

//class emit
template<typename CharType>
class emit : public interval
{
public:
	typedef std::basic_string<CharType> string_type;
	typedef std::basic_string<CharType>& string_ref_type;

private:
	string_type d_keyword;

public:
	emit() : interval(-1, -1), d_keyword() {}

	emit(size_t start, size_t end, string_type keyword)
		: interval(start, end),
		  d_keyword(keyword) {}

	string_type get_keyword() const 
	{
		return string_type(d_keyword);
	}

	bool is_empty() const
	{
		return (get_start() == -1 && get_end() == -1);
	}
};

//class token
template<typename CharType>
class token
{
public:
	enum token_type
	{
		TYPE_FRAGMENT,
		TYPE_MATCH
	};

	using string_type = std::basic_string<CharType>;
	using string_ref_type = std::basic_string<CharType>&;
	using emit_type = emit<CharType>;

private:
	token_type		d_type;
	string_type		d_fragment;
	emit_type		d_emit;

public:
	token(string_ref_type fragment)
		: d_type(TYPE_FRAGMENT),
		  d_fragment(fragment),
		  d_emit() {}

	token(string_ref_type fragment, const emit_type& e)
		: d_type(TYPE_MATCH),
		  d_fragment(fragment),
		  d_emit() {}

	bool is_match() const
	{
		return d_type == TYPE_MATCH;
	}

	string_type get_fragment() const
	{
		return string_type(d_fragment);
	}

	emit_type get_emit() const
	{
		return d_emit;
	}
};

//class state
template<typename CharType>
class state
{
public:
	typedef state<CharType>*					ptr;
	typedef std::unique_ptr<state<CharType>>	unique_ptr;
	typedef std::basic_string<CharType>			string_type;
	typedef std::basic_string<CharType>&		string_ref_type;
	typedef std::set<string_type>				string_collection;
	typedef std::vector<ptr>					state_collection;
	typedef std::vector<CharType>				transition_collection;

private:
	size_t				d_depth;
	ptr					d_root;
	std::map<CharType, unique_ptr> d_success;
	ptr					d_failure;
	string_collection	d_emits;

public:
	state() : state(0) {}

	state(size_t depth)
		: d_depth(depth),
		  d_root(depth == 0 ? this : nullptr),
		  d_success(),
		  d_failure(nullptr),
		  d_emits() {}

	ptr next_state(CharType character) const
	{
		return next_state(character, false);
	}

	ptr next_state_ignore_root_state(CharType character) const
	{
		return next_state(character, true);
	}

	ptr add_state(CharType character)
	{
		auto next = next_state_ignore_root_state(character);
		if (next == nullptr)
		{
			next = new state<CharType>(d_depth + 1);
			d_success[character].reset(next);
		}
		return next;
	}

	size_t get_depth() const
	{
		return d_depth;
	}

	void add_emit(string_ref_type keyword)
	{
		d_emits.insert(keyword);
	}

	void add_emit(const string_collection& emits)
	{
		for (const auto& e : emits)
		{
			string_type str(e);
			add_emit(str);
		}
	}

	string_collection get_emits() const { return d_emits; }  

	ptr failure() const { return d_failure; }  

	void set_failure(ptr fail_state) { d_failure = fail_state; }  

	state_collection get_states() const 
	{  
		state_collection result;  
		for (auto it = d_success.cbegin(); it != d_success.cend(); ++it) 
		{  
			result.push_back(it->second.get());  
		}  
		return state_collection(result);  
	}  

	transition_collection get_transitions() const 
	{  
		transition_collection result;  
		for (auto it = d_success.cbegin(); it != d_success.cend(); ++it) 
		{  
			result.push_back(it->first);  
		}  
		return transition_collection(result);  
	}  

private:  
	ptr next_state(CharType character, bool ignore_root_state) const {  
		ptr result = nullptr;  
		auto found = d_success.find(character);  
		if (found != d_success.end()) {  
			result = found->second.get();  
		} else if (!ignore_root_state && d_root != nullptr) {  
			result = d_root;  
		}  
		return result;  
	}  
};

template<typename CharType>  
class basic_trie 
{  
public:  
	using string_type = std::basic_string < CharType > ;  
	using string_ref_type = std::basic_string<CharType>&;  

	typedef state<CharType>         state_type;  
	typedef state<CharType>*        state_ptr_type;  
	typedef token<CharType>         token_type;  
	typedef emit<CharType>          emit_type;  
	typedef std::vector<token_type> token_collection;  
	typedef std::vector<emit_type>  emit_collection;  

	class config 
	{  
		bool d_allow_overlaps;  
		bool d_only_whole_words;  
		bool d_case_insensitive;  

		public:  
		config()  
			: d_allow_overlaps(true)  
			  , d_only_whole_words(false)  
			  , d_case_insensitive(false) {}  

		bool is_allow_overlaps() const { return d_allow_overlaps; }  
		void set_allow_overlaps(bool val) { d_allow_overlaps = val; }  

		bool is_only_whole_words() const { return d_only_whole_words; }  
		void set_only_whole_words(bool val) { d_only_whole_words = val; }  

		bool is_case_insensitive() const { return d_case_insensitive; }  
		void set_case_insensitive(bool val) { d_case_insensitive = val; }  
	};  

private:  
	std::unique_ptr<state_type> d_root;  
	config                      d_config;  
	bool                        d_constructed_failure_states;  

public:  
	basic_trie(): basic_trie(config()) {}  

	basic_trie(const config& c)  
		: d_root(new state_type())  
		, d_config(c)  
		, d_constructed_failure_states(false) {}  

	basic_trie& case_insensitive() 
	{  
		d_config.set_case_insensitive(true);  
		return (*this);  
	}  

	basic_trie& remove_overlaps() 
	{  
		d_config.set_allow_overlaps(false);  
		return (*this);  
	}  

	basic_trie& only_whole_words() 
	{  
		d_config.set_only_whole_words(true);  
		return (*this);  
	}  

	void insert(string_type keyword) 
	{  
		if (keyword.empty())  
			return;  
		state_ptr_type cur_state = d_root.get();  
		for (const auto& ch : keyword) 
		{  
			cur_state = cur_state->add_state(ch);  
		}  
		cur_state->add_emit(keyword);  
	}  

	template<class InputIterator>  
	void insert(InputIterator first, InputIterator last) 
	{  
		for (InputIterator it = first; first != last; ++it) 
		{  
			insert(*it);  
		}  
	}  

	token_collection tokenise(string_type text) 
	{  
		token_collection tokens;  
		auto collected_emits = parse_text(text);  
		size_t last_pos = -1;  
		for (const auto& e : collected_emits) 
		{  
			if (e.get_start() - last_pos > 1) 
			{  
				tokens.push_back(create_fragment(e, text, last_pos));  
			}  
			tokens.push_back(create_match(e, text));  
			last_pos = e.get_end();  
		}  
		if (text.size() - last_pos > 1) 
		{  
			tokens.push_back(create_fragment(typename token_type::emit_type(), text, last_pos));  
		}  
		return token_collection(tokens);  
	}  

	emit_collection parse_text(string_type text) 
	{  
		check_construct_failure_states();  
		size_t pos = 0;  
		state_ptr_type cur_state = d_root.get();  
		emit_collection collected_emits;  
		for (auto c : text) 
		{  
			if (d_config.is_case_insensitive()) 
			{  
				c = std::tolower(c);  
			}  
			cur_state = get_state(cur_state, c);  
			store_emits(pos, cur_state, collected_emits);  
			pos++;  
		}  
		if (d_config.is_only_whole_words()) 
		{  
			remove_partial_matches(text, collected_emits);  
		}  
		if (!d_config.is_allow_overlaps()) 
		{  
			interval_tree<emit_type> tree(typename interval_tree<emit_type>::interval_collection(collected_emits.begin(), collected_emits.end()));  
			auto tmp = tree.remove_overlaps(collected_emits);  
			collected_emits.swap(tmp);  
		}  
		return emit_collection(collected_emits);  
	}  

	void construct_failure_states() 
	{  
		std::queue<state_ptr_type> q;  
		for (auto& depth_one_state : d_root->get_states()) 
		{  
			depth_one_state->set_failure(d_root.get());  
			q.push(depth_one_state);  
		}  
		d_constructed_failure_states = true;  

		while (!q.empty()) 
		{  
			auto cur_state = q.front();  
			for (const auto& transition : cur_state->get_transitions()) 
			{  
				state_ptr_type target_state = cur_state->next_state(transition);  
				q.push(target_state);  

				state_ptr_type trace_failure_state = cur_state->failure();  
				while (trace_failure_state->next_state(transition) == nullptr) 
				{  
					trace_failure_state = trace_failure_state->failure();  
				}  
				state_ptr_type new_failure_state = trace_failure_state->next_state(transition);  
				target_state->set_failure(new_failure_state);  
				target_state->add_emit(new_failure_state->get_emits());  
			}  
			q.pop();  
		}  
	}  

private:  
	token_type create_fragment(const typename token_type::emit_type& e, string_ref_type text, size_t last_pos) const 
	{  
		auto start = last_pos + 1;  
		auto end = (e.is_empty()) ? text.size() : e.get_start();  
		auto len = end - start;  
		typename token_type::string_type str(text.substr(start, len));  
		return token_type(str);  
	}  

	token_type create_match(const typename token_type::emit_type& e, string_ref_type text) const 
	{  
		auto start = e.get_start();  
		auto end = e.get_end() + 1;  
		auto len = end - start;  
		typename token_type::string_type str(text.substr(start, len));  
		return token_type(str, e);  
	}  

	void remove_partial_matches(string_ref_type search_text, emit_collection& collected_emits) const 
	{  
		size_t size = search_text.size();  
		emit_collection remove_emits;  
		for (const auto& e : collected_emits) 
		{  
			if ((e.get_start() == 0 || !std::isalpha(search_text.at(e.get_start() - 1))) &&  
					(e.get_end() + 1 == size || !std::isalpha(search_text.at(e.get_end() + 1)))  
			   ) 
			{  
				continue;  
			}  
			remove_emits.push_back(e);  
		}  
		for (auto& e : remove_emits) 
		{  
			collected_emits.erase(std::find(collected_emits.begin(), collected_emits.end(), e));  
		}  
	}  

	state_ptr_type get_state(state_ptr_type cur_state, CharType c) const 
	{  
		state_ptr_type result = cur_state->next_state(c);  
		while (result == nullptr) 
		{  
			cur_state = cur_state->failure();  
			result = cur_state->next_state(c);  
		}  
		return result;  
	}  

	void check_construct_failure_states() 
	{  
		if (!d_constructed_failure_states) 
		{  
			construct_failure_states();  
		}  
	}  

	void store_emits(size_t pos, state_ptr_type cur_state, emit_collection& collected_emits) const 
	{  
		auto emits = cur_state->get_emits();  
		if (!emits.empty()) 
		{  
			for (const auto& str : emits) 
			{  
				auto emit_str = typename emit_type::string_type(str);  
				collected_emits.push_back(emit_type(pos - emit_str.size() + 1, pos, emit_str));  
			}  
		}  
	}  
};  

typedef basic_trie<char>     trie;  
typedef basic_trie<wchar_t>  wtrie;  
typedef basic_trie<char16_t> utrie;


#endif









