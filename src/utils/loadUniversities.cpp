#include "utils/loadUniversities.hpp"

#include <QString>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QStandardItem>

namespace Utils {
    void loadUniversities(const QString &path, QHash<QString, QStringList> &departments_by_university, QStandardItemModel *university_model) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Could not open" << path;
            return;
        }

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
        if (error.error != QJsonParseError::NoError || !doc.isArray()) {
            qWarning() << "Invalid universities JSON:" << error.errorString();
            return;
        }

        for (const QJsonValue &value : doc.array()) {
            QJsonObject uni = value.toObject();
            QString key = uni["name"].toString();
            if (key.isEmpty())
                continue;

            QStringList departments;
            for (const QJsonValue &dept : uni["departments"].toArray())
                departments << dept.toString();
            departments_by_university.insert(key, departments);

            QStandardItem *item = new QStandardItem(QIcon(uni["icon"].toString()), key);
            item->setData(key, Qt::UserRole);
            university_model->appendRow(item);
        }
    }
}