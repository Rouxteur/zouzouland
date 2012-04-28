#ifndef MAIL_H
#define MAIL_H

#include <string>

# ifdef _WIN32
const std::string path("D:/mails");
# else
const std::string path("../mails");
# endif // _WIN32

class Mail
{
 public:
  Mail();
  ~Mail();
  const std::string	&getTo() const;
  void			setTo(const std::string &);
  const std::string	&getFrom() const;
  void			setFrom(const std::string &);
  const std::string	&getContent() const;
  void			setContent(const std::string &);
  bool			save();

 private:
  std::string		to_;
  std::string		from_;
  std::string		content_;
  bool			saved_;
};
#endif
