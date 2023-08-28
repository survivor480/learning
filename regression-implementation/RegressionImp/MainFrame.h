#pragma once
#include <wx/wx.h>
#include <string.h>
#include <vector>
#include <string>
#include "./CSVReader/header/csv_reader.h"

class MainFrame :public wxFrame
{
public:
	std::string filename;

	wxTextCtrl* control;

	wxPanel* linear_regression_panel;

	wxPanel* multiple_linear_regression_panel;

	wxComboBox* x_options;

	wxComboBox* y_options;

	std::vector<std::string> dependencies;

	MainFrame(const wxString& title);

	void comboTabAction(wxKeyEvent& event);

	wxListBox* parameter_list;

	CSV_Reader* read;

	void OnLinearRegressionOpenClicked(wxCommandEvent& evt);

	void OnMultipleLinearRegressionOpenClicked(wxCommandEvent& evt);

	void OnLinearRegressionSendClicked(wxCommandEvent& evt);

	void OnMultipleLinearRegressionSendClicked(wxCommandEvent& evt);

};

