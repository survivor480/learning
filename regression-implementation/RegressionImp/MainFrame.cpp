#include "MainFrame.h"
#include <iostream>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/wx.h>
#include <wx/window.h>
#include <wx/dynarray.h>
#include <string>
#include <wx/arrstr.h>

#include "./CSVReader/header/csv_reader.h"


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	// Create a top-level panel to hold all the contents of the frame
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create the wxNotebook widget
	wxNotebook* notebook = new wxNotebook(panel, wxID_ANY, wxPoint(10, 10), wxSize(100, 200), wxNB_TOP);

	CreateStatusBar();

	// Add 2 pages to the wxNotebook widget
	//wxTextCtrl* textCtrl1 = new wxTextCtrl(notebook, wxID_ANY, L"Tab 1 Contents");
	//notebook->AddPage(textCtrl1, L"Linear Regression");
	//wxTextCtrl* textCtrl2 = new wxTextCtrl(notebook, wxID_ANY, L"Tab 2 Contents");
	//notebook->AddPage(textCtrl2, L"Multiple Linear Regression");

	// Set up the sizer for the panel
	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(notebook, 1, wxEXPAND);
	panel->SetSizer(panelSizer);

	// Set up the sizer for the frame and resize the frame
	// according to its contents
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->SetMinSize(250, 100);
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);

	linear_regression_panel = new wxPanel(notebook, wxID_ANY);
	
	// If we dont include a panel, the button will go on to occupy the entire width and height of the frame
	control = new wxTextCtrl(linear_regression_panel, wxID_ANY, wxEmptyString, wxPoint(10, 2), wxSize(700, 20), wxTE_LEFT, wxDefaultValidator, wxTextCtrlNameStr);

	wxButton* button_2 = new wxButton(linear_regression_panel, wxID_OPEN, "Open", wxPoint(720, 0), wxSize(80, 24));

	button_2->Bind(wxEVT_BUTTON, &MainFrame::OnLinearRegressionOpenClicked, this);

	notebook->AddPage(linear_regression_panel, L"Linear Regression");









	multiple_linear_regression_panel = new wxPanel(notebook, wxID_ANY);

	control = new wxTextCtrl(multiple_linear_regression_panel, wxID_ANY, wxEmptyString, wxPoint(10, 2), wxSize(700, 20), wxTE_LEFT, wxDefaultValidator, wxTextCtrlNameStr);

	wxButton* button_3 = new wxButton(multiple_linear_regression_panel, wxID_OPEN, "Open", wxPoint(720, 0), wxSize(80, 24));

	button_3->Bind(wxEVT_BUTTON, &MainFrame::OnMultipleLinearRegressionOpenClicked, this);

	notebook->AddPage(multiple_linear_regression_panel, L"Multiple Linear Regression");

	//wxComboBox* box = new wxComboBox(panel, wxID_ANY, _T(""), wxDefaultPosition, wxDefaultSize,
	//	0, NULL, wxTE_PROCESS_ENTER | wxTE_PROCESS_TAB);
	//box->GetEventHandler()->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MainFrame::comboTabAction));

}

void MainFrame::comboTabAction(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_TAB)
		Navigate(wxNavigationKeyEvent::IsForward);
	else
		event.Skip();
}

void MainFrame::OnLinearRegressionOpenClicked(wxCommandEvent& evt) {
	wxFileDialog* openFileDialog = new wxFileDialog(this);

	std::string file;

	if (openFileDialog->ShowModal() == wxID_OK) {
		file = openFileDialog->GetPath();
		wxString fileName = openFileDialog->GetPath();
		*control << fileName;
	}


	CSV_Reader *read = new CSV_Reader(file);

	wxGrid* grid = new wxGrid(linear_regression_panel, -1, wxPoint(0, 125), wxSize(800, 475));

	grid->CreateGrid(read->data_1[read->dependencies[0]].size(), read->dependencies.size());

	wxFont *font = new wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int i = 0; i < read->dependencies.size(); i++) {
		grid->SetCellValue(0, i, read->dependencies[i]);
		grid->SetCellFont(0, i, *font);

	}	

	for (int i = 0; i < read->dependencies.size(); i++) {
		for (int j = 1; j < read->data_1[read->dependencies[i]].size(); j++) {
			grid->SetCellValue(j, i, read->data_1[read->dependencies[i]][j]);
		}
	}

	wxString* combolist = new wxString[read->dependencies.size()];

	for (int i = 0; i < read->dependencies.size(); i++) {
		combolist[i] = read->dependencies[i];
	}

	x_options = new wxComboBox(linear_regression_panel, wxID_ANY, "Select X value", wxPoint(100, 70), wxSize(100, 30), read->dependencies.size(), combolist, wxCB_DROPDOWN, wxDefaultValidator, wxComboBoxNameStr);

	y_options = new wxComboBox(linear_regression_panel, wxID_ANY, "Select Y value", wxPoint(400, 70), wxSize(100, 30), read->dependencies.size(), combolist, wxCB_DROPDOWN, wxDefaultValidator, wxComboBoxNameStr);

	wxButton* button_4 = new wxButton(linear_regression_panel, wxID_OPEN, "Send", wxPoint(600, 70), wxSize(80, 24));

	button_4->Bind(wxEVT_BUTTON, &MainFrame::OnLinearRegressionSendClicked, this);
}

void MainFrame::OnMultipleLinearRegressionOpenClicked(wxCommandEvent& evt) {
	wxFileDialog* openFileDialog = new wxFileDialog(this);

	std::string file;

	if (openFileDialog->ShowModal() == wxID_OK) {
		file = openFileDialog->GetPath();
		wxString fileName = openFileDialog->GetPath();
		*control << fileName;
	}


	read = new CSV_Reader(file);

	wxGrid* grid = new wxGrid(multiple_linear_regression_panel, -1, wxPoint(0, 125), wxSize(800, 475));

	grid->CreateGrid(read->data_1[read->dependencies[0]].size(), read->dependencies.size());

	wxFont* font = new wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int i = 0; i < read->dependencies.size(); i++) {
		grid->SetCellValue(0, i, read->dependencies[i]);
		grid->SetCellFont(0, i, *font);

	}

	for (int i = 0; i < read->dependencies.size(); i++) {
		for (int j = 1; j < read->data_1[read->dependencies[i]].size(); j++) {
			grid->SetCellValue(j, i, read->data_1[read->dependencies[i]][j]);
		}
	}

	wxString* combolist = new wxString[read->dependencies.size()];

	for (int i = 0; i < read->dependencies.size(); i++) {
		combolist[i] = read->dependencies[i];
	}

	parameter_list = new wxListBox(multiple_linear_regression_panel, wxID_ANY, wxPoint(70, 70), wxSize(300, 70), read->dependencies.size(), combolist, wxLB_MULTIPLE, 
		wxDefaultValidator, wxListBoxNameStr);

	wxButton* button_4 = new wxButton(multiple_linear_regression_panel, wxID_ANY, "Send", wxPoint(600, 70), wxSize(80, 24));

	button_4->Bind(wxEVT_BUTTON, &MainFrame::OnMultipleLinearRegressionSendClicked, this);
}


void MainFrame::OnLinearRegressionSendClicked(wxCommandEvent& evt) {
	wxString str = "The value selected for x is " + x_options->GetStringSelection() + " and y is " + y_options->GetStringSelection() + ".";
	wxLogStatus(str);
}

void MainFrame::OnMultipleLinearRegressionSendClicked(wxCommandEvent& evt) {
	wxArrayInt* selected_option_list = new wxArrayInt(0);

	//parameter_list->GetSelections(*selected_option_list);

	wxArrayString temp_str = parameter_list->GetStrings();

	wxString str = "The positions for x are: ";
	
	/*if (selected_option_list->Index(0) < 0) {

	}*/

	vector<string> dependents;

	for (int i = 0; i < read->dependencies.size(); i++) {
		if (temp_str.Index(read->dependencies[i], false)) {
			if (i == read->dependencies.size() - 1) {
				dependents.push_back(read->dependencies[i]);

				str += read->dependencies[i] + ".";
				continue;
			}
			dependents.push_back(read->dependencies[i]);

			str += read->dependencies[i] + ", ";
		};

	}

	wxLogStatus(str);

}
