#include <wx/wx.h>
#include <wx/html/htmlwin.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <cmark.h>

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class MyFrame : public wxFrame
{
    public:
        MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    private:
        void RenderMarkdown();
        wxHtmlWindow *htmlControl;
        wxTextCtrl *markdownControl;
        wxTimer renderTimer;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello Everyone!", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    const auto MarkdownExample = R"(
# Hello World
This is a simple wxWidgets application that displays a "Hello World!" message in a text control.

## Features
- wxFrame
- wxTextCtrl

# How to Implement This in C++

Really, you can just implement the code below:

```cpp
#include <wx/wx.h>
#include <wx/textctrl.h>

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class MyFrame : public wxFrame
{
    public:
        MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello Everyone!", wxDefaultPosition, wxDefaultSize);
    wxTextCtrl *textCtrl = new wxTextCtrl(frame, wxID_ANY, "Hello World!");
    frame->Show(true);
    return true;
}
```

# Learn More

Visit [wxWidgets Documentation](https://docs.wxwidgets.org/3.2) to learn more about wxWidgets.
    )";

    wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY);

    htmlControl = new wxHtmlWindow(splitter, wxID_ANY);

    markdownControl = new wxTextCtrl(splitter, wxID_ANY, MarkdownExample, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    markdownControl->SetValue(MarkdownExample);
    markdownControl->SetFont(wxFontInfo(12).Family(wxFONTFAMILY_TELETYPE));

    splitter->SetSashGravity(0.5);
    splitter->SetMinimumPaneSize(FromDIP(200));
    splitter->SplitVertically(markdownControl, htmlControl);

    renderTimer.SetOwner(this);

    Bind(wxEVT_TIMER, 
            [this](wxTimerEvent& event) {
                RenderMarkdown();
            });

    markdownControl->Bind(wxEVT_TEXT, 
            [this](wxCommandEvent& event) {
                if (!renderTimer.IsRunning())
                {
                    renderTimer.StartOnce(500); // Delay rendering for 500 ms
                }
            });
    htmlControl->Bind(wxEVT_HTML_LINK_CLICKED, 
            [this](wxHtmlLinkEvent& event) {
                wxLaunchDefaultBrowser(event.GetLinkInfo().GetHref());
            });


    RenderMarkdown();
}


void MyFrame::RenderMarkdown()
{
    auto text = markdownControl->GetValue();
    auto buffer = text.utf8_str();

    auto htmlText = cmark_markdown_to_html(buffer.data(), buffer.length(), CMARK_OPT_DEFAULT);

    htmlControl->SetPage(htmlText);

    free(htmlText);
}
