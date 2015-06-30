//http://martinfowler.com/articles/collection-pipeline
//http://martinfowler.com/articles/refactoring-pipelines.html

#include <cassert>

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

struct author {
	std::string company_;
	std::string twitter_handle_;
};

std::vector<std::string> getTwitterHandlesFromAuthors(std::vector<author> authors, const std::string& company) {
	/*
	//original loop
	std::vector<std::string> result;
	std::vector<author>::const_iterator it = authors.begin();
	for (; it != authors.end(); ++it) {
		if (it->company_ == company) {
			if (!it->twitter_handle_.empty()) {
				result.push_back(it->twitter_handle_);
			}
		} 
	}
	*/

	/*
	//refactor 1
	std::vector<author> company_authors;
	std::copy_if(authors.begin(), authors.end(), std::back_inserter(company_authors), [company](const author& a){ return a.company_ == company; });
	std::vector<std::string> result;
	std::vector<author>::const_iterator it = company_authors.begin();
	for (; it != company_authors.end(); ++it) {
		if (!it->twitter_handle_.empty()) {
			result.push_back(it->twitter_handle_);
		}
	}
	*/

	//refactor 2
	/*
	std::vector<author> company_authors;
	//filter
	std::copy_if(authors.begin(), authors.end(), std::back_inserter(company_authors), [company](const author& a){ return a.company_ == company && !a.twitter_handle_.empty(); });
	std::vector<std::string> result(company_authors.size());
	//map
	std::transform(company_authors.begin(), company_authors.end(), result.begin(), [](const author& a){ return a.twitter_handle_; });
	*/

	//refactor 2
	//filter
	auto end = std::remove_if(authors.begin(), authors.end(), [&company](const author &a) { return a.company_ != company || a.twitter_handle_.empty();	});
	//map
	std::vector<std::string> result;
	std::transform(authors.begin(), end, std::back_inserter(result), [](const author& a) { return a.twitter_handle_; });

	return result;

	// ideal
	/*
	return std::vector<std::string>{ range(authors)
		| view::filter([&company](author& a){ return a.company_ != company || a.twitter_handle_.empty();})
		| view::map([](author& a){ return a.twitter_handle_})};
	*/
}

int main() {

	std::vector<author> authors = { {"the company", "@name"}, {"other company", "@not_this"}, {"yet another company", "@this_neither"}, {"the company", ""}, {"the company", "@another_name"}};
	std::vector<std::string> twitter_handles;
	twitter_handles = getTwitterHandlesFromAuthors(authors, "the company");
	assert(twitter_handles.size() == 2);
	assert(twitter_handles[0] == "@name");
	assert(twitter_handles[1] == "@another_name");

	std::cout << "OK" << std::endl;
}

