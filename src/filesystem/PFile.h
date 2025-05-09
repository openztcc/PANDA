#ifndef PFILE_H
#define PFILE_H

// Project
#include "PFileSystem.h"
#include "PZip.h"

// Qt
#include <QDir>

/*
This is an abstraction layer above the two supported virtual filesystems:
PZip and PFileSystem.
It provides a common interface for file operations such as read, write, remove, etc.
*/

enum FileType {
    Zip,
    Other
};

class PFile : public QObject {
    Q_OBJECT
public:
    PFile(QObject *parent = nullptr, const QString &filePath = "", FileType type = FileType::Other);
    ~PFile() override = default;

    std::unique_ptr<IVirtualFilesystem> createFilesystem(const QString &filePath, FileType type = FileType::Other) const;

    // mount point functions
    void setRootPath(const QString &path);
    QString rootPath() const;

    // file operations - relative to root path
    QSharedPointer<PFileData> read(const QString &filePath);
    QVector<QSharedPointer<PFileData>> readAll(const QStringList& validFolders = {}, const QStringList &validExts = {});
    bool write(const QSharedPointer<PFileData> &data);
    bool remove(const QStringList &filesToRemove);
    bool remove(const QString &fileToRemove);
    bool exists(const QString &filePath);

    // move/rename
    bool move(const QString &filePath, const QString &newLocation);
    bool copy(const QString &filePath, const QString &newLocation);
    bool rename(const QString &filePath, const QString &newFileName);

    // directory operations
    // bool makeDir(const QString &dirPath);
    // bool dirExists(const QString &dirPath);
    // bool removeDir(const QString &dirPath);
    // bool listFiles(const QString &dirPath);
private:
    std::unique_ptr<IVirtualFilesystem> m_file; // pointer to the virtual filesystem
    QString m_rootPath; // root path of the zip file
};

#endif // PFILE_H
