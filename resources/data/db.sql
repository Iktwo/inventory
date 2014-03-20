-- ** Products ** table to store products information
-- idProduct: id
-- name: name of product, can't be null

CREATE TABLE IF NOT EXISTS "products" ("idProduct" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "name"  NOT NULL, "quantity")

INSERT OR REPLACE INTO "products" ("idProduct", "name", "quantity") VALUES (1, "Product 1", 5)
INSERT OR REPLACE INTO "products" ("idProduct", "name", "quantity") VALUES (2, "Product 2", 10)
INSERT OR REPLACE INTO "products" ("idProduct", "name", "quantity") VALUES (3, "Product 3", 18)
