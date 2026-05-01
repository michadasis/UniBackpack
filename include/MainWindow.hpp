// Author: Apostolos Chalis 2026 <achalis@csd.auth.gr>
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStringListModel> 
#include <QModelIndex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    	Q_OBJECT
	
	public:
    		MainWindow(QWidget *parent = nullptr);
		~MainWindow(); 
	
	private slots: 
		void on_university_selection(const QModelIndex &index);

	private:
    		Ui::MainWindow *ui;

		QStringListModel *university_model; 
		QStringListModel *department_model; 

		bool showing_universities;
};

#endif // MAINWINDOW_HPP
