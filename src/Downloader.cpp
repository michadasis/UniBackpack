// Authors: Apostolos Chalis 2026 <achalis@csd.auth.gr>, Ioannis Michadasis 2026 <cs05415@uowm.gr>
#include "Downloader.hpp"

#include <QDebug> 
#include <QString> 
#include <QStringList>
#include <QStandardPaths>
#include <QProcess> //for qt to be able to open child processes

QString Downloader::check_package_manager() {
	if (!QStandardPaths::findExecutable("pacman").isEmpty()){
		qDebug() << "Pacman found.";
		return "pacman";
	} else if (!QStandardPaths::findExecutable("apt").isEmpty()) {
		qDebug() << "Apt found.";
		return "apt";
	} else {
		qDebug() << "No supported package manager found.";
		return "Unsupported";
	}
}

QStringList Downloader::read_package_list(bool standard_package_manager) {
    // TODO
}

void Downloader::download_via_pacman(const QStringList &list_to_be_downloaded) {
    // TODO
}

void Downloader::download_via_apt(const QStringList &list_to_be_downloaded) {
    if (list_to_be_downloaded.isEmpty()) {
        qDebug() << "No packages to install.";
        emit download_completed(false);
        return;
    }

    QProcess *process = new QProcess(this);

    connect(process, &QProcess::readyReadStandardOutput, this, [=]() {
        emit status_message(process->readAllStandardOutput());
    });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [=](int exitCode, QProcess::ExitStatus) {
        emit download_completed(exitCode == 0);
        process->deleteLater();
    });

    QStringList args;
    args << "install" << "-y" << list_to_be_downloaded;

    qDebug() << "Installing via apt:" << list_to_be_downloaded;
    process->start("apt", args);
}
