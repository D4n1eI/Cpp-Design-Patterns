#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

enum class OutputFormat
{
    markdown,
    html
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;

    virtual void start(std::ostringstream& oss)
    {
    }

    virtual void end(std::ostringstream& oss)
    {
    }

    virtual void add_list_item(std::ostringstream& oss,
                               const std::string& item) = 0;
};

struct MarkdownListStrategy : ListStrategy
{
    void add_list_item(std::ostringstream& oss,
                       const std::string& item) override
    {
        oss << "* " << item << "\n";
    }
};

struct HtmlListStrategy : ListStrategy
{
    void start(std::ostringstream& oss) override
    {
        oss << "<ul>\n";
    }

    void end(std::ostringstream& oss) override
    {
        oss << "</ul>\n";
    }

    void add_list_item(std::ostringstream& oss,
                       const std::string& item) override
    {
        oss << "  <li>" << item << "</li>\n";
    }
};

struct TextProcessor
{
    void clear()
    {
        oss.str("");
        oss.clear();
    }

    void append_list(const std::vector<std::string>& items)
    {
        list_strategy->start(oss);

        for (const auto& item : items)
        {
            list_strategy->add_list_item(oss, item);
        }

        list_strategy->end(oss);
    }

    void set_output_format(OutputFormat format)
    {
        switch (format)
        {
        case OutputFormat::markdown:
            list_strategy = std::make_unique<MarkdownListStrategy>();
            break;

        case OutputFormat::html:
            list_strategy = std::make_unique<HtmlListStrategy>();
            break;
        }
    }

    std::string str() const
    {
        return oss.str();
    }

private:
    std::ostringstream oss;
    std::unique_ptr<ListStrategy> list_strategy;
};

int main()
{
    std::vector<std::string> items{"Foo", "Bar", "Baz"};

    TextProcessor tp;

    tp.set_output_format(OutputFormat::markdown);
    tp.append_list(items);
    std::cout << tp.str() << "\n";

    tp.clear();

    tp.set_output_format(OutputFormat::html);
    tp.append_list(items);
    std::cout << tp.str() << "\n";

    return 0;
}