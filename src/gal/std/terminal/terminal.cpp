
#include <gal/std/terminal/terminal.hpp>
#include <gal/std/terminal/command_set.hpp>

gal::std::stringstream::stringstream(sp::shared_ptr<gal::std::__terminal_data> t): t_(t) {
	assert(t_);
}
gal::std::stringstream::stringstream(gal::std::stringstream&& ss):
	t_(::std::move(ss.t_))
{}
gal::std::stringstream::~stringstream() {
	if(t_) {
		t_->lines_.push_back(t_->ss_.str());
		t_->ss_.str(::std::string());
	}
}





gal::std::terminal::terminal():
	lines_max_(20),
	prompt_end_("$ ")
{}
void					gal::std::terminal::push(char c) {
	line_.push_back(c);
}
void					gal::std::terminal::eval(::std::string const & s) {

	auto self = sp::dynamic_pointer_cast<gal::std::terminal>(shared_from_this());

	if(cs_) {
		(*cs_)(self, line_);
	} else {
		operator<<("No commands exist.");
	}

}
void					gal::std::terminal::enter() {

	
	operator<<(prompt_end_) << line_;
	
	eval(line_);
	
	line_.clear();
	
	return;

	while(lines_.size() > lines_max_) {
		lines_.pop_front();
	}

}



