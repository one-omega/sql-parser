#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cstring>
#include <cmath>

std::map<std::string, std::map<std::string, FieldInfo>> table_map;
std::map<std::string, std::map<std::string, int>> table_name_map;
void build_table_data();
TmpValue* get_field_value(char* c_field_name, std::string table_name, std::vector<std::string> values);
Expr *dfs_expr(Expr *expr, std::vector<std::string> values, std::string table_name);
Expr* deepCopyExpr(Expr* expr);
void deleteExpr(Expr* expr);

Session session;

int length = 0;

void update_rows(UpdateRecord* update_record_ctx) {
    if (!check_use_db())
    {
        printf("have not use db\n");
        return;
    }
    char *db = session.db;
    // std::cout << db << std::endl;
    build_table_data();

    char *c_table_name = update_record_ctx->table_name;
    Expr *where_case = update_record_ctx->where_case;

    char file_path[100];
    std::sprintf(file_path, "./data/%s/%s.txt", db, c_table_name);
    std::ifstream file(file_path);

    if (!file.is_open())
    {
        std::cout << "无法打开表文件:" << file_path << std::endl;
    }

    std::string line;

    std::string table_name_str(c_table_name);

    std::vector<std::vector<std::string>> updated_data; // 用于保存更新后的数据

    while (std::getline(file, line))
    {
        std::vector<std::string> values;
        std::stringstream ss(line);

        std::string data;
        while (ss >> data)
        {
            values.push_back(data);
        }
        int ret = 0;
        std::string table_name_str(c_table_name);
        // std::cout << "before where" << std::endl;
        if (where_case != NULL) {
            // std::cout << "where_case:" << where_case << std::endl;
            Expr* tmp = deepCopyExpr(where_case);
            // std::cout << "tmp:" << tmp << std::endl;
            Expr *root = dfs_expr(tmp, values, table_name_str);
            // std::cout << "after dfs" << std::endl;
            // printf("judge:%d,left:%d,op:%d,right:%d\n",
            //        root->judge, root->left->judge, root->type, root->right->judge);
            if (root->type == _INT && root->intval != 0)
            {
                ret = 1;
            }
            else if (root->type == _CHAR && root->strval != NULL)
            {
                ret = 1;
            }
            else if (root->judge == 1)
            {
                ret = 1;
            }
            deleteExpr(root);
        } else {
            ret = 1;
        }

        if (ret)
        {
            // std::cout << "ret:" << ret << std::endl;
            auto& update_map = update_record_ctx->update_map_wrap->update_map;
            // std::cout << "size:" << update_map.size() << std::endl;
            for (auto it = update_map.begin(); it != update_map.end(); ++it) {
                // std::cout << "update..." << std::endl; 
                const std::string& field_name = it->first;
                // std::cout << "field_name:" << field_name << std::endl;
                const TmpValue& tmp_value = it->second;

                int index = table_name_map[table_name_str][field_name] - 1;
                int type = tmp_value.type;
                if (type == _INT) {
                    std::string strval = std::to_string(tmp_value.intvalue);
                    // std::cout << "value:" << strval << std::endl;
                    values[index] = strval;
                } else if (type == _CHAR) {
                    values[index] = tmp_value.strvalue;
                    // std::cout << "value:" << tmp_value.strvalue << std::endl;
                }
            }
        }
        // std::cout << "ret:" << ret << std::endl;
        updated_data.push_back(values);
    }

    file.close();

    // std::cout << "overwrite..." << std::endl;
    // 打开同一个文件进行写操作
    std::ofstream outfile(file_path);
    if (!outfile.is_open())
    {
        std::cout << "无法打开表文件进行写操作:" << file_path << std::endl;
        return;
    }

    // 将更新后的数据写回文件
    for (const auto& updated_values : updated_data) {
        for (size_t i = 0; i < updated_values.size(); ++i) {
            // std::cout << updated_values[i] << std::endl;
            outfile << updated_values[i];
            if (i != updated_values.size() - 1) {
                outfile << " ";
            }
        }
        outfile << std::endl;
    }
    outfile.close();

    std::cout << "update success" << std::endl;
    // old_db = session.db;
    // flag = 0;
    // session.db = NULL;
    // if (!flag) {
    //     update_rows(update_record_ctx);
    // }
    delete update_record_ctx->where_case;
    delete update_record_ctx;
}

void select_rows(SelectRecord* select_record_ctx) {
    if (!check_use_db())
    {
        printf("have not use db\n");
        return;
    }
    char *db = session.db;
    // std::cout << db << std::endl;
    build_table_data();

    // std::cout << "table_map:" << std::endl;
    // for (const auto &table : table_map)
    // {
    //     std::cout << "Table: " << table.first << std::endl;
    //     for (const auto &field : table.second)
    //     {
    //         std::cout << "Field: " << field.first << ", Type: " << field.second.type << ", Length: " << field.second.length << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    // // 输出 table_name_map
    // std::cout << "table_name_map:" << std::endl;
    // for (const auto &table : table_name_map)
    // {
    //     std::cout << "Table: " << table.first << std::endl;
    //     for (const auto &field : table.second)
    //     {
    //         std::cout << "Field: " << field.first << ", Value: " << field.second << std::endl;
    //     }
    //     std::cout << std::endl;
    // }


    // std::cout << select_record_ctx << std::endl;
    char *c_table_name = select_record_ctx->table_name;
    Expr *where_case = select_record_ctx->where_case;
    std::vector<std::string> select_names = select_record_ctx->select_names;

    char file_path[100];
    std::sprintf(file_path, "./data/%s/%s.txt", db, c_table_name);
    std::ifstream file(file_path);

    if (!file.is_open())
    {
        std::cout << "无法打开表文件:" << file_path << std::endl;
    }

    std::string line;

    std::string table_name_str(c_table_name);

    // std::cout << "table_name: " << table_name_str << std::endl;
    while (std::getline(file, line))
    {
        std::vector<std::string> values;
        std::stringstream ss(line);

        std::string data;
        while (ss >> data)
        {
            values.push_back(data);
        }
        // for (int i = 0; i < values.size(); ++i) {
        //     std::cout << values[i] << " ";
        // }
        // std::cout << std::endl;
        // length = 0;
        int ret = 0;
        if (where_case != NULL) {
            // std::cout << "where_case:" << where_case << std::endl;
            Expr* tmp = deepCopyExpr(where_case);
            // std::cout << "tmp:" << tmp << std::endl;
            Expr *root = dfs_expr(tmp, values, table_name_str);
            // std::cout << "after dfs" << std::endl;
            // printf("judge:%d,left:%d,op:%d,right:%d\n",
            //        root->judge, root->left->judge, root->type, root->right->judge);
            if (root->type == _INT && root->intval != 0)
            {
                ret = 1;
            }
            else if (root->type == _CHAR && root->strval != NULL)
            {
                ret = 1;
            }
            else if (root->judge == 1)
            {
                ret = 1;
            }
            deleteExpr(root);
        } else {
            ret = 1;
        }

        if (ret)
        {
            if (select_names.size() == 0) {
                for (int i = 0; i < values.size(); ++i) {
                    std::cout << values[i] << " ";
                }
                std::cout << std::endl;
            } else {
                for (int i = 0; i < select_names.size(); ++i) {
                    auto select_name = select_names[i];
                    int index = table_name_map[table_name_str][select_name];
                    auto value = values[index-1];
                    std::cout << value << " ";
                }
                std::cout << std::endl;
            }
        }
    }
    file.close();
    // session.db = NULL;
}

void delete_row(DeleteRecord *delete_record_ctx)
{
    // printf("delete....\n");
    // Expr* expr_ = delete_record_ctx->where_case;
    // printf("expr:%s %d %d...\n", expr_->left->strval, expr_->type,
    //     expr_->right->intval);
    // std::cout << "expr_->left->left:" << (expr_->left->left == NULL) << std::endl;
    // std::cout << "expr_->left->right:" << (expr_->left->right == NULL) << std::endl;
    // std::cout << "expr_->right->left:" << (expr_->right->left == NULL) << std::endl;
    // std::cout << "expr_->right->right:" << (expr_->right->right == NULL) << std::endl;
    if (!check_use_db())
    {
        printf("have not use db\n");
        return;
    }
    char *db = session.db;
    build_table_data();

    // 输出 table_map
    // std::cout << "table_map:" << std::endl;
    // for (const auto &table : table_map)
    // {
    //     std::cout << "Table: " << table.first << std::endl;
    //     for (const auto &field : table.second)
    //     {
    //         std::cout << "Field: " << field.first << ", Type: " << field.second.type << ", Length: " << field.second.length << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    // // 输出 table_name_map
    // std::cout << "table_name_map:" << std::endl;
    // for (const auto &table : table_name_map)
    // {
    //     std::cout << "Table: " << table.first << std::endl;
    //     for (const auto &field : table.second)
    //     {
    //         std::cout << "Field: " << field.first << ", Value: " << field.second << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    char *table_name = delete_record_ctx->table_name;
    Expr *where_case = delete_record_ctx->where_case;

    char file_path[100];
    std::sprintf(file_path, "./data/%s/%s.txt", db, table_name);
    std::ifstream file(file_path);

    if (!file.is_open())
    {
        std::cout << "无法打开表文件:" << file_path << std::endl;
    }

    std::string line;

    std::string table_name_str(table_name);

    std::vector<std::string> lines_to_keep;
    while (std::getline(file, line))
    {
        std::vector<std::string> values;
        std::stringstream ss(line);

        std::string data;
        while (ss >> data)
        {
            values.push_back(data);
        }
        // for (int i = 0; i < values.size(); ++i) {
        //     std::cout << values[i] << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "where_case:" << where_case << std::endl;
        // length = 0;
        Expr* tmp = deepCopyExpr(where_case);
        // std::cout << "tmp:" << tmp << std::endl;
        Expr *root = dfs_expr(tmp, values, table_name_str);
        int ret = 0;
        // printf("judge:%d,left:%d,op:%d,right:%d\n",
        //        root->judge, root->left->judge, root->type, root->right->judge);
        if (root->type == _INT && root->intval != 0)
        {
            ret = 1;
        }
        else if (root->type == _CHAR && root->strval != NULL)
        {
            ret = 1;
        }
        else if (root->judge == 1)
        {
            ret = 1;
        }
        if (!ret)
        {
            lines_to_keep.push_back(line);
        }
        deleteExpr(root);
    }
    file.close();
    // 删除原文件
    std::remove(file_path);
    std::ofstream new_file(file_path);

    if (!new_file.is_open())
    {
        std::cout << "无法创建新文件:" << file_path << std::endl;
        return;
    }

    for (const auto &line : lines_to_keep)
    {
        new_file << line << std::endl;
    }

    printf("delete success\n");
    new_file.close();
    // session.db = NULL;
}

Expr *dfs_expr(Expr *expr, std::vector<std::string> values, std::string table_name)
{
    std::string db_str(session.db);
    Expr *left = expr->left;
    Expr *right = expr->right;
    int type = expr->type;
    // printf("now_type:%d\n", expr->type);
    if (left == NULL && right == NULL)
    {

        if (expr->type == _INT)
        {
            // printf("int_val:%d\n", expr->intval);
        }
        else if (expr->type == _CHAR)
        {
            // printf("str_val:%d\n", expr->strval);
        } else if (type == _ID) {
            // printf("id:%s\n", expr->strval);
            // std::string field_name(expr->strval);
            // int index = table_name_map[table_name][field_name];
            // FieldInfo field_info = table_map[table_name][field_name];
            // int value_index = index - 1;
            // std::string value = values[value_index];
            // expr->type = field_info.type;
            // // printf("new_type:%d\n", expr->type);
            // if (expr->type == _INT)
            // {
            //     expr->intval = std::stoi(value);
            //     printf("id_val:%d\n", expr->intval);
            // }
            // else if (expr->type == _CHAR)
            // {
            //     expr->strval = new char[value.length() + 1];
            //     std::strcpy(expr->strval, value.c_str());
            //     printf("id_val:%d\n", expr->strval);
            // }
        }

        return expr;
    }
    else
    {
        if (left != NULL)
        {
            left = dfs_expr(left, values, table_name);
        }
        if (right != NULL)
        {
            right = dfs_expr(right, values, table_name);
        }
        if (left == NULL || right == NULL) printf("exist null\n");

        if (type == _AND)
        {
            expr->judge = (left->judge && right->judge);
        }
        else if (type == _OR)
        {
            expr->judge = (left->judge || right->judge);
        }
        else
        {
            int left_value = std::max(left->intval, left->judge);
            int right_value = std::max(right->intval, right->judge);
            // printf("%d %d\n", left_value, right_value);

            char* left_str_value = left->strval;
            char* right_str_value = right->strval;

            int left_type = expr->left->type;
            if (left->type == _ID) {
                TmpValue* tmp_value = get_field_value(left->strval, table_name, values);
                if (tmp_value->type == _INT) {
                    left_value = tmp_value->intvalue;
                } else if (tmp_value->type == _CHAR) {
                    left_str_value = tmp_value->strvalue;
                }
                left_type = tmp_value->type;
            }

            switch (type)
            {
            case _EQUAL:
                if (left_type == _INT) {
                    expr->judge = (left_value == right_value);
                } else if (left_type == _CHAR) {
                    if (left_str_value != NULL && right_str_value != NULL) {
                        expr->judge = (strcmp(left_str_value, right_str_value) == 0);
                    } else {
                        expr->judge = 0;
                    }
                }
                break;
            case _NOT_EQUAL:
                if (left_type == _INT) {
                    expr->judge = (left_value != right_value);
                } else if (left_type == _CHAR) {
                    if (left_str_value != NULL && right_str_value != NULL) {
                        expr->judge = (strcmp(left_str_value, right_str_value) != 0);
                    } else {
                        expr->judge = 1;
                    }
                }
                break;
            case _LESS:
                expr->judge = (left_value < right_value);
                break;
            case _MORE:
                expr->judge = (left_value > right_value);
                break;
            case _LESS_EQUAL:
                expr->judge = (left_value <= right_value);
                break;
            case _MORE_EQUAL:
                expr->judge = (left_value >= right_value);
                break;
            default:
                printf("expr->type is invalid\n");
                expr->judge = -1; // null
                break;
            }
        }
    }

    return expr;
}

void build_table_data()
{
    if (!check_use_db())
    {
        return;
    }
    char *db = session.db;

    char table_filepath[100];
    std::sprintf(table_filepath, "./data/%s/sys.dat", db);
    std::ifstream file(table_filepath);
    if (!file.is_open())
    {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string tableName, fieldName, type_str;
        int index, length;
        ss >> tableName >> index >> fieldName >> type_str >> length;

        FieldInfo fieldInfo;
        if (type_str == "char")
        {
            fieldInfo.type = _CHAR;
        }
        else if (type_str == "int")
        {
            fieldInfo.type = _INT;
        }

        // Parse length if it exists
        if (fieldInfo.type != _INT)
        {
            fieldInfo.length = length;
        }

        table_map[tableName][fieldName] = fieldInfo;
        table_name_map[tableName][fieldName] = index;
    }

    file.close();
}

int check_use_db()
{
    return session.db != NULL;
}

Expr* deepCopyExpr(Expr* expr)
{
    // printf("copy....");
    length++;
    if (length >= 50) {
        length = 0;
        return NULL;
    }

    if (expr == NULL) {
        length = 0;
        return NULL;
    }

    Expr* newExpr = new Expr;
    newExpr->type = expr->type;
    newExpr->strval = NULL;

    if (expr->strval != NULL)
    {
        size_t strLength = std::strlen(expr->strval);
        newExpr->strval = new char[strLength + 1];
        std::strcpy(newExpr->strval, expr->strval);
    }

    newExpr->intval = expr->intval;
    newExpr->judge = expr->judge;

    newExpr->left = deepCopyExpr(expr->left);
    newExpr->right = deepCopyExpr(expr->right);

    return newExpr;
}

void deleteExpr(Expr* expr)
{
    if (expr == nullptr)
        return;

    delete[] expr->strval;

    deleteExpr(expr->left);
    deleteExpr(expr->right);

    delete expr;
}

TmpValue* get_field_value(char* c_field_name, std::string table_name, std::vector<std::string> values) {
    std::string field_name(c_field_name);
    int index = table_name_map[table_name][field_name];
    FieldInfo field_info = table_map[table_name][field_name];
    int value_index = index - 1;
    std::string value = values[value_index];

    TmpValue* tmp_value = (TmpValue*) malloc(sizeof(TmpValue));
    int type = field_info.type;
    if (value == "NULL") {
        type = _CHAR;
    }
    tmp_value->type = type;
    if (type == _INT) {
        tmp_value->intvalue = std::stoi(value);
    } else if (type == _CHAR) {
        char* field_value = (char*)malloc(sizeof(char)*(value.length()+1));
        std::strcpy(field_value, value.c_str());
        tmp_value->strvalue = field_value;
    }
    return tmp_value;
}
