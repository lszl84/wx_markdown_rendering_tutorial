#include <wx/wx.h>

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

}

