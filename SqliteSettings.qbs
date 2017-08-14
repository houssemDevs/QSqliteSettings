import qbs

Project {
    name: "SqliteSettings"

    qbsSearchPaths: "../qbs_modules"

    Product {
        type: project.staticBuild ? "staticlibrary" : "dynamiclibrary"
        Depends { name: "Qt"; submodules: [ "core", "sql" ] }
        Depends { name: "cpp" }

        cpp.cxxLanguageVersion: "c++11"
        cpp.defines: [
            "QT_DEPRECATED_WARNINGS",
            "QT_DISABLE_DEPRECATED_BEFORE=0x060000"
        ]

        Export {
            Depends { name: "cpp" }
            cpp.includePaths: [product.sourceDirectory]
            cpp.defines: product.type == "staticlibrary" ? ["SQLITESETTINGS_STATIC"] : []
        }

        files: [
            "qsqlitesettings.cpp",
            "sqliteconnection.cpp",
            "sqliteconnection.h",
            "sqlitesettings_read_write.h",
        ]

        Group {
            condition: product.type == "dynamiclibrary"
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
            qbs.install: project.installInclude
        }

        Properties {
            condition: product.type == "dynamiclibrary"
            cpp.defines: ["SQLITESETTINGS_SHARED"]
        }
        Properties {
            condition: product.type == "staticlibrary"
            cpp.defines: ["SQLITESETTINGS_STATIC"]
        }


    }
}
