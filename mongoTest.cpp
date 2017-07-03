#include <iostream>
#include <cstdint>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <string>
#include <vector>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/result/insert_one.hpp>

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::finalize;
using namespace std;

int main()
{
    //创建mongo实例
    mongocxx::instance instance{};
    //建立客户端连接
    mongocxx::client client{mongocxx::uri{}};
    //获取数据库
    mongocxx::database db = client["test"];
    //获取集合
    mongocxx::collection coll = db["testCollection"];
    //创建流构建器
    auto builder = bsoncxx::builder::stream::document{};

#if 0
    //创建一个文档
    bsoncxx::document::value doc_value = builder
        << "name" << "wangmazi"
        << "age" << 11 
        << finalize;
    //如果要使用文档,需要先转成view
    bsoncxx::document::view view = doc_value.view();    
    bsoncxx::document::element element = view["name"];  //获取view中的字段值(元素)
    string name = element.get_utf8().value.to_string(); //转换字段值格式，得到string类型的字段值(这里name字段是字符串类型)
    //element = view["age"];
    //string age = element.get_utf8().value.to_string();
    cout << name << "\t" << endl;
#endif


#if 0
    //插入单个文档
    //bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one((bsoncxx::v_noabi::document::value&&)doc_value);
    //  const bsoncxx::types::value& id_value = mongocxx::result::insert_one::inserted_id(coll);    //获取id(主键),这里转化失败了；如果不需要主键id可忽略此行代码；
#endif


#if 0
    //插入多个文档
    vector<bsoncxx::document::value> documents;
    for(int i = 0; i < 4; ++i)
    {
        documents.push_back(bsoncxx::builder::stream::document{} << "name" << i << "age" << i << finalize);
    }
    coll.insert_many(documents);
#endif


#if 0
    //查询单个文档
    //{$or:[{name:'wangmazi'},{name:0}]
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result = coll.find_one(document{}<<"$or"
            <<open_array
            << open_document << "name" << "wangmazi" << close_document
            << open_document << "name" << 0 << close_document
            << close_array
            << finalize);
    if(maybe_result)
    {
        cout << bsoncxx::to_json(*maybe_result) << endl;
    }
#endif

    
#if 0
    //查询多个文档
    mongocxx::cursor cursor = coll.find(document{} << "$or"
            << open_array
            << open_document << "name" << 1 << close_document
            << open_document << "age" << 2 << close_document
            << close_array
            << finalize);
    for(auto doc:cursor)
    {
        cout << bsoncxx::to_json(doc) << endl;
    }
#endif


#if 0    
    //删除单个文档
    if(coll.delete_one(document{} << "name" << 0 << finalize))
    {
        cout << "name = 0 这个文档删除成功" << endl;
    }
    else
        cout << "name = 0 这个文档删除失败" << endl;
#endif


#if 0
    //删除多个文档
    bsoncxx::stdx::optional<mongocxx::result::delete_result> result = coll.delete_many(document{}
            << "hello" << "world" 
            << finalize);
    if(result)
    {
        cout << result->deleted_count() << endl;
    }
#endif


    //创建集合索引
    coll.create_index(document{}
            << "name" << 1 << "age" << 1
            << finalize);
    

    return 0;
}
