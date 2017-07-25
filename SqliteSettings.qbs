import qbs

Project {
    minimumQbsVersion: "1.7.1"

    Product {
        type: [ "dynamiclibrary" ]
        Depends { name: "Qt"; submodules: [ "core", "sql" ] }
        Depends { name: "cpp" }

        Export {
            Depends { name: "cpp" }
            cpp.includePaths: [product.sourceDirectory]
        }

        cpp.cxxLanguageVersion: "c++11"
        cpp.defines: [
            "QT_DEPRECATED_WARNINGS",
            "QT_DISABLE_DEPRECATED_BEFORE=0x060000"
        ]

        files: [
            "qsqlitesettings.cpp",
            "sqliteconnection.cpp",
            "sqliteconnection.h",
            "sqlitesettings_read_write.h",
        ]

        Group {
            name: "install library"
            fileTagsFilter: product.type
            qbs.install: true
        }
        Group {
            name: "install include"
            files: [
                "sqlite_settings_globals.h",
                "qsqlitesettings.h",
                "QSqliteSettings"
            ]
            overrideTags: false
            qbs.installDir: "include"
            qbs.install: true
        }

        Properties {
            condition: product.type == "dynamiclibrary"
            cpp.defines: ["SQLITESETTINGS_LIBRARY"]
        }
        Properties {
            condition: product.type == "staticlibrary"
            cpp.defines: ["SQLITESETTINGS_STATIC"]
        }


    }
}
