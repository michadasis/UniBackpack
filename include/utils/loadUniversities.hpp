#ifndef LOAD_UNIVERSITIES_HPP
#define LOAD_UNIVERSITIES_HPP

#include <QString>
#include <QStandardItem>

namespace Utils {
    void loadUniversities(const QString &path,
                              QHash<QString, QStringList> &departments_by_university,
                              QStandardItemModel *university_model);
}

#endif // LOAD_UNIVERSITIES_HPP
