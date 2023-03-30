#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DTitlebar>
#include <DProgressBar>
#include <DFontSizeManager>

#include <QPropertyAnimation>
#include <QDate>
#include <QLayout>
//
#include <QDir>
#include <QStandardItemModel>
#include <QListView>
#include <QTableView>
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication app(argc, argv);
        app.setOrganizationName("Harbin Engineering University");
        app.setApplicationName("uos-appmanager");
        app.setApplicationVersion("0.0.1");
        app.setProductIcon(QIcon(":/images/logo.svg"));
        app.setProductName("应用启动器");
        app.setApplicationDescription("基于uos的开机自动启动的启动器");
        // 提供中文界面支持
        app.loadTranslator();
        app.setApplicationDisplayName(QCoreApplication::translate("Main", "DTK Application"));

        // 保存程序的窗口主题设置
        DApplicationSettings as;
        Q_UNUSED(as)
        // 创建一个QStandardItemModel
        QStandardItemModel *model = new QStandardItemModel();
        model->setHorizontalHeaderLabels(QStringList() << "应用程序名称" << "操作");
//        model->setHorizontalHeaderLabels(QStringList() << "Name" << "Icon");
        // 获取所有的.desktop文件
        QDir dir("/usr/share/applications");
        // 有些应用程序不是以.desktop结尾的
//        QStringList filters;
//        filters << "*.desktop";
//        dir.setNameFilters(filters);
        QStringList files = dir.entryList();
        // 解析每个.desktop文件，获取应用程序的名称和图标路径
        foreach(QString file, files) {
            QFile f("/usr/share/applications/" + file);
            if(f.open(QIODevice::ReadOnly)) {
                QTextStream in(&f);
                QString line = in.readLine();
                QString name, icon;
                while(!line.isNull()) {
                    if(line.startsWith("Name=")) {
                        name = line.mid(5);
                    } else if(line.startsWith("Icon=")) {
//                        icon = line.mid(5);
                    }
                    line = in.readLine();
                }
                f.close();
                // 将应用程序的名称和图标添加到QStandardItemModel中
                // 图标的路径并不统一，待完善
                if(!name.isEmpty()) {
                    QStandardItem *item = new QStandardItem(name);
                    if(!icon.isEmpty()) {
                        item->setIcon(QIcon("/usr/share/icons/" + icon));
                    }
                    model->appendRow(item);
                }
            }
        }
        // 创建一个QTableView控件，并将QStandardItemModel绑定到该控件上
        QTableView *tableView = new QTableView();
        tableView->setModel(model);
        tableView->setColumnWidth(0, 300);
        // 将QTableView控件加入到DMainWindow中的中心部件中
        DMainWindow window;
        window.titlebar()->setIcon(QIcon(":/images/logo.svg"));
        window.titlebar()->setTitle("应用启动器");
        // 设置标题，宽度不够会隐藏标题文字
        window.setMinimumSize(QSize(600, 200));
        window.setGeometry(100, 100, 800, 600);
        window.setCentralWidget(tableView);
        window.show();

        Dtk::Widget::moveToCenter(&window);
        return app.exec();
}
