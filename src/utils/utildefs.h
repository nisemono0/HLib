#pragma once

#include <Qt>

namespace MyDataRoles {
    enum MyDataRoles {
        Title = Qt::UserRole,
        FilePath = Qt::UserRole + 1,
        FileHash = Qt::UserRole + 2,
        Tags = Qt::UserRole + 3
    };
};

namespace MyTheme {
    enum MyTheme { DARK_MAROON, DARK_GREEN, DARK_PURPLE, FUSION, WINDOWS };
};

namespace SetImageOption {
    enum SetImageOption { NextImage, PrevImage };
}