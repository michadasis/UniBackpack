// Author: Apostolos Chalis 2026 <achalis@csd.auth.gr>

#include "ui_MainWindow.h"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QListView>
#include <QListView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) {
	
	ui->setupUi(this);

	university_model = new QStringListModel(this);
	department_model = new QStringListModel(this);

	QStringList universities = {
		"Aristotle University of Thessaloniki", 
		"University of Western Macedonia", 
		"University of Macedonia"
	};

	university_model->setStringList(universities);

	ui->listView->setModel(university_model);
	showing_universities = true;

	connect(ui->listView, &QListView::clicked, this, &MainWindow::on_university_selection);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_university_selection(const QModelIndex &index) {
	if (showing_universities) {
		QString selectedUni = university_model->data(index, Qt::DisplayRole).toString();
		qDebug() << "Selected: " << selectedUni;

		QStringList departments;

		if (selectedUni == "Aristotle University of Thessaloniki") {
			departments << "Back to Universities" 
						<< "Informatics" 
						<< "Physics";
		} else if (selectedUni == "University of Western Macedonia") {
			departments << "Back to Universities" 
						<< "Informatics" 
						<< "Mechanical Engineering";
		} else if (selectedUni == "University of Macedonia") {
			departments << "Back to Universities" 
						<< "Applied Informatics" 
						<< "Economics";
		}

		department_model->setStringList(departments);
		ui->listView->setModel(department_model);
		showing_universities = false; 
	} else {
		if (index.row() == 0) {
			ui->listView->setModel(university_model);
			showing_universities = true;
		} else {
			QString selectedDept = department_model->data(index, Qt::DisplayRole).toString();
			qDebug() << "Installing for department: " << selectedDept;
		}
	}
}
