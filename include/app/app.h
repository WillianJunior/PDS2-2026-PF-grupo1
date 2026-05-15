#pragma once

namespace edu_social {

/**
 * @brief Coordinates application bootstrap and HTTP server startup.
 *
 * App is responsible for infrastructure orchestration. It opens the database,
 * applies the schema and registers the endpoints that are already available in
 * the current checkpoint.
 *
 * The class does not contain domain rules. Its role is limited to wiring the
 * database, the HTTP surface and the runtime process.
 */
class App {
public:
    /**
     * @brief Starts the backend process.
     *
     * The method creates the database file when needed, applies the schema,
     * registers the routes and blocks the process while the HTTP server is
     * running.
     *
     * @return Process exit code.
     */
    int run();
};

}
