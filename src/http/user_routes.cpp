#include "http/user_routes.h"

#include <chrono>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <sqlite3.h>

#include "http/not_implemented_response.h"

namespace edu_social::http {

namespace {

std::string current_timestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_buf{};
#ifdef _WIN32
    gmtime_s(&tm_buf, &time_t_now);
#else
    gmtime_r(&time_t_now, &tm_buf);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
}

std::string hash_password(const std::string& password) {
    const std::size_t hash = std::hash<std::string>{}(password + "edu_social_salt_2026");
    std::ostringstream oss;
    oss << std::hex << hash;
    return oss.str();
}

void print_user_created(const std::string& username, const std::string& email, const std::string& full_name) {
    const std::string green  = "\033[1;32m";
    const std::string cyan   = "\033[36m";
    const std::string bold   = "\033[1m";
    const std::string reset  = "\033[0m";

    std::cout << "\n";
    std::cout << green << "+--------------------------------------+" << reset << "\n";
    std::cout << green << "|   ** Novo usuario criado! **         |" << reset << "\n";
    std::cout << green << "+--------------------------------------+" << reset << "\n";
    std::cout << green << "|" << reset << cyan  << "  Nome:      " << reset << bold << full_name  << reset << "\n";
    std::cout << green << "|" << reset << cyan  << "  Username:  " << reset << bold << "@" << username << reset << "\n";
    std::cout << green << "|" << reset << cyan  << "  Email:     " << reset << bold << email << reset << "\n";
    std::cout << green << "+--------------------------------------+" << reset << "\n\n";
}

}

void register_user_routes(crow::SimpleApp& app, edu_social::SQLiteConnection& db) {
    CROW_ROUTE(app, "/users/<int>").methods(crow::HTTPMethod::Get)([](int) {
        return make_not_implemented_response("GET", "/users/{id}");
    });

    CROW_ROUTE(app, "/users").methods(crow::HTTPMethod::Post)([&db](const crow::request& req) {
        const auto body = crow::json::load(req.body);
        if (!body) {
            crow::json::wvalue err;
            err["error"] = "Invalid JSON body.";
            crow::response res(400);
            res.set_header("Content-Type", "application/json");
            res.body = err.dump();
            return res;
        }

        if (!body.has("username") || !body.has("full_name") || !body.has("email") || !body.has("password")) {
            crow::json::wvalue err;
            err["error"] = "Fields username, full_name, email and password are required.";
            crow::response res(422);
            res.set_header("Content-Type", "application/json");
            res.body = err.dump();
            return res;
        }

        const std::string username  = body["username"].s();
        const std::string full_name = body["full_name"].s();
        const std::string email     = body["email"].s();
        const std::string password  = body["password"].s();
        const std::string bio       = body.has("bio") ? std::string(body["bio"].s()) : "";
        const std::string now       = current_timestamp();
        const std::string pw_hash   = hash_password(password);

        const std::string sql =
            "INSERT INTO users (username, full_name, email, password_hash, bio, created_at, updated_at) "
            "VALUES (?, ?, ?, ?, ?, ?, ?);";

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db.raw_handle(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            crow::json::wvalue err;
            err["error"] = "Database error.";
            crow::response res(500);
            res.set_header("Content-Type", "application/json");
            res.body = err.dump();
            return res;
        }

        sqlite3_bind_text(stmt, 1, username.c_str(),  -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, full_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, email.c_str(),     -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, pw_hash.c_str(),   -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, bio.c_str(),       -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 6, now.c_str(),       -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 7, now.c_str(),       -1, SQLITE_TRANSIENT);

        const int rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc == SQLITE_CONSTRAINT) {
            crow::json::wvalue err;
            err["error"] = "Username or email already in use.";
            crow::response res(409);
            res.set_header("Content-Type", "application/json");
            res.body = err.dump();
            return res;
        }

        if (rc != SQLITE_DONE) {
            crow::json::wvalue err;
            err["error"] = "Failed to create user.";
            crow::response res(500);
            res.set_header("Content-Type", "application/json");
            res.body = err.dump();
            return res;
        }

        const int new_id = static_cast<int>(sqlite3_last_insert_rowid(db.raw_handle()));

        print_user_created(username, email, full_name);

        crow::json::wvalue response_body;
        response_body["id"]         = new_id;
        response_body["username"]   = username;
        response_body["full_name"]  = full_name;
        response_body["email"]      = email;
        response_body["bio"]        = bio;
        response_body["created_at"] = now;

        crow::response res(201);
        res.set_header("Content-Type", "application/json");
        res.body = response_body.dump();
        return res;
    });
}

}
