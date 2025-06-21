#! /bin/sqlite

DROP TABLE IF EXISTS "cart_effets";
CREATE TABLE "cart_effets" (
	"ef_index"	INTEGER,
	"ef_name"	TEXT,
	PRIMARY KEY("ef_index")
);
DROP TABLE IF EXISTS "cart_types";
CREATE TABLE "cart_types" (
	"type_index"	INTEGER,
	"type_name"	TEXT,
	PRIMARY KEY("type_index")
);
DROP TABLE IF EXISTS "carts";
CREATE TABLE "carts" (
	"cart_index" INTEGER PRIMARY KEY AUTOINCREMENT,
	"cart_name"	TEXT,
	"effet_id"	INTEGER DEFAULT 1,
	"type_id"	INTEGER DEFAULT 1,
	"cart_level"	INTEGER DEFAULT 1,
	"cart_generate"	REAL DEFAULT 0,
	FOREIGN KEY("effet_id") REFERENCES "cart_effets",
	FOREIGN KEY("type_id") REFERENCES "cart_types"
);
INSERT INTO "cart_effets" ("ef_index","ef_name") VALUES (1,'NULL');
INSERT INTO "cart_effets" ("ef_index","ef_name") VALUES (2,'ObjHeal');
INSERT INTO "cart_effets" ("ef_index","ef_name") VALUES (3,'ObjDamage');
INSERT INTO "cart_effets" ("ef_index","ef_name") VALUES (4,'EquipRange');
INSERT INTO "cart_effets" ("ef_index","ef_name") VALUES (5,'EquipDefence');
INSERT INTO "cart_effets" ("ef_index","ef_name") VALUES (6,'EquipAttack');
INSERT INTO "cart_types" ("type_index","type_name") VALUES (1,'item');
INSERT INTO "cart_types" ("type_index","type_name") VALUES (2,'equip');
INSERT INTO "cart_types" ("type_index","type_name") VALUES (3,'monster');
INSERT INTO "carts" ("cart_index","cart_name","effet_id","type_id","cart_level","cart_generate") VALUES (1,'sheep',1,3,1,0.5);
INSERT INTO "carts" ("cart_index","cart_name","effet_id","type_id","cart_level","cart_generate") VALUES (2,'wolf',1,3,2,0.0);
INSERT INTO "carts" ("cart_index","cart_name","effet_id","type_id","cart_level","cart_generate") VALUES (3,'cerberus',1,3,3,0.0);
INSERT INTO "carts" ("cart_index","cart_name","effet_id","type_id","cart_level","cart_generate") VALUES (4,'potion',2,1,1,0.4);
INSERT INTO "carts" ("cart_index","cart_name","effet_id","type_id","cart_level","cart_generate") VALUES (5,'fireball',3,1,1,0.3);
INSERT INTO "carts" ("cart_index","cart_name","effet_id","type_id","cart_level","cart_generate") VALUES (6,'minautor',1,3,4,0.0);
INSERT INTO "carts" ("cart_index","cart_name","effet_id","type_id","cart_level","cart_generate") VALUES (7,'shield',5,2,1,0.2);
INSERT INTO "carts" ("cart_index","cart_name","effet_id","type_id","cart_level","cart_generate") VALUES (8,'sword',6,2,1,0.2);
INSERT INTO "carts" ("cart_index","cart_name","effet_id","type_id","cart_level","cart_generate") VALUES (9,'bow',4,2,1,0.1);

