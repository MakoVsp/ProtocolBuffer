#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::AddressBook address_book;
    tutorial::Person* person = address_book.add_people();
    // 填充数据
    person->set_name("zypper");
    tutorial::Person::PhoneNumber* phone_number = person->add_phones();
    phone_number->set_number("18600805776");
    phone_number->set_type(tutorial::Person::MOBILE);
    std::string addString = person->SerializeAsString();

    // 读取数据
    tutorial::Person* person2 = address_book.add_people();
    person2->ParseFromString(addString);
    qDebug() << "name = " << person2->name().c_str();
    qDebug() << "number = " << person2->phones(tutorial::Person::MOBILE).number().c_str();

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return app.exec();
}
