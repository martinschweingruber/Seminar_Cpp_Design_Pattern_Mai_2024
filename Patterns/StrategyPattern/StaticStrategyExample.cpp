// ===========================================================================
// StaticStrategyExample.cpp // Static Strategy Pattern Example
// ===========================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <initializer_list>

// =====================================================================
// dynamic strategy pattern example

enum class Format { Markdown, Html };

struct IListStrategy
{
    virtual ~IListStrategy() {}

    virtual void start(std::ostringstream& oss) = 0;
    virtual void end(std::ostringstream& oss) = 0;
    virtual void add_list_item(std::ostringstream& oss, const std::string& item) = 0;
};

struct MarkdownListStrategy : public IListStrategy
{
    virtual void start(std::ostringstream& oss) override {};

    virtual void end(std::ostringstream& oss) override {};

    virtual void add_list_item(std::ostringstream& oss, const std::string& item) override {
        oss << " - " << item << std::endl; 
    }
};

struct HtmlListStrategy : public IListStrategy
{
    virtual void start(std::ostringstream& oss) override {
        oss << "<ul>" << std::endl; 
    }

    virtual void end(std::ostringstream& oss) override {
        oss << "</ul>" << std::endl; 
    }

    virtual void add_list_item(std::ostringstream& oss, const std::string& item) override {
        oss << "\t<li>" << item << "</li>" << std::endl;
    }
};

class TextProcessor
{
private:
    std::unique_ptr<IListStrategy> m_list_strategy;

    std::ostringstream m_oss;

public:
    void clear() {
        m_oss.str("");
        m_oss.clear();
    }

    void append_list(std::initializer_list<std::string> items) {

        m_list_strategy->start(m_oss);    // indirect call

        for (const auto& item : items) {
            m_list_strategy->add_list_item(m_oss, item);
        }

        m_list_strategy->end(m_oss);
    }

    void set_output_format(Format format) {

        switch (format) {
        case Format::Markdown:
            m_list_strategy = std::make_unique<MarkdownListStrategy>();
            break;

        case Format::Html:
            m_list_strategy = std::make_unique<HtmlListStrategy>();
            break;
        }
    }

    std::string str() { return m_oss.str(); }
};

void test_dynamic_strategy_example ()
{
    // markdown
    TextProcessor tp;
    tp.set_output_format(Format::Markdown);    // Laufzeit 
    tp.append_list({ "foo", "bar", "baz" });
    std::cout << tp.str() << std::endl;

    // html
    tp.clear();
    tp.set_output_format(Format::Html);
    tp.append_list({ "foo", "bar", "baz" });
    std::cout << tp.str() << std::endl;
}

// =====================================================================
// static strategy pattern example

template<typename TListStrategy>
class TextProcessorEx
{
private:
    TListStrategy m_list_strategy;   // value
    std::ostringstream m_oss;

public:
    void append_list(std::initializer_list<std::string> items) 
    {
        m_list_strategy.start(m_oss);

        for (auto& item : items) {
            m_list_strategy.add_list_item(m_oss, item);
        }

        m_list_strategy.end(m_oss);  // .   DIRECT CALL // direkter Aufruf
    }

    std::string str() const { return m_oss.str(); }
};

struct MarkdownListStrategyEx
{
    void start(std::ostringstream& oss) {};

    void end(std::ostringstream& oss) {};

    void add_list_item(std::ostringstream& oss, const std::string& item) {
        oss << " - " << item << std::endl;
    }
};

struct HtmlListStrategyEx
{
    void start(std::ostringstream& oss) {
        oss << "<ul>" << std::endl;
    }

    void end(std::ostringstream& oss) {
        oss << "</ul>" << std::endl;
    }

    void add_list_item(std::ostringstream& oss, const std::string& item) {
        oss << "\t<li>" << item << "</li>" << std::endl;
    }
};

void test_static_strategy_example ()
{
    // markdown
    TextProcessorEx<MarkdownListStrategyEx> tp1;   // Übersetzungszeit
    tp1.append_list({ "foo", "bar", "baz" });
    std::cout << tp1.str() << std::endl;

    // html
    TextProcessorEx<HtmlListStrategyEx> tp2;
    tp2.append_list({ "foo", "bar", "baz" });
    std::cout << tp2.str() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
