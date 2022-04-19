#include "pbsqlite.h"
#include "person.pb.h"
#include <iostream>

using namespace aa;



int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    Person a;

    auto person = Person();
    person.set_name("Jonh");
    auto person2 = Person();
    person2.set_id(100);
    person2.set_name("Davi11111111111111d");
    auto db = std::make_shared<pbsqlite::Database>("example.db", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
    
    db->CreateTableIfNotExists(person, "id");
    db->ReplaceInto(person);
    db->ReplaceInto(person2);
    
    auto rs = db->Select<Person>("WHERE id>=0");
    // std::vector<Person> rs = db->Select("WHERE id>=0");

    // EXPECT_TRUE(rs.size() >= 2);
    // EXPECT_EQ(rs[0].id(), 0);
    // EXPECT_EQ(rs[1].id(), 2);
    // EXPECT_EQ(rs[1].name(), "David");

    std::cout << rs[1].id() << rs[1].name() << std::endl;

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}