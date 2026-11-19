-- Crear usuario en cada nodo (uso % porque es prototipo no para producción)

-- CREATE USER 'ddbs'@'%' IDENTIFIED BY '';
-- GRANT SELECT, INSERT, UPDATE, CREATE ON 'db'.* TO 'ddbs'@'%';

-- Abrir puerto 3306 (con firewalld)
-- sudo firewall-cmd --permanent --add-port=3306/tcp
-- sudo firewall-cmd --reload


-- Sucursal morelia
CREATE DATABASE IF NOT EXISTS morelia_store;

CREATE TABLE IF NOT EXISTS morelia_store.client(
    client_id INT AUTO_INCREMENT UNIQUE,
    name      VARCHAR(100) NOT NULL,
    flname    VARCHAR(50) NOT NULL,
    mlname    VARCHAR(50) NOT NULL,
    rfc       CHAR(13) UNIQUE,

    PRIMARY KEY(rfc)
);

CREATE TABLE IF NOT EXISTS morelia_store.address(
    address_id  INT UNIQUE AUTO_INCREMENT,
    street      VARCHAR(200) NOT NULL,
    house_num   VARCHAR(10) NOT NULL,
    state       VARCHAR(200) NOT NULL,
    postal_code CHAR(5) NOT NULL,
    client      CHAR(13) NOT NULL UNIQUE,

    FOREIGN KEY(client) REFERENCES client(rfc)
);

CREATE TABLE IF NOT EXISTS morelia_store.store(
    store_id INT UNIQUE AUTO_INCREMENT,
    host        VARCHAR(15),
    db_name  VARCHAR(100) UNIQUE
);

-- Sucursal uruapan
-- CREATE DATABASE IF NOT EXISTS uruapan_store;
-- 
-- CREATE TABLE IF NOT EXISTS uruapan_store.client(
--     client_id INT AUTO_INCREMENT UNIQUE,
--     name      VARCHAR(100) NOT NULL,
--     flname    VARCHAR(50) NOT NULL,
--     mlname    VARCHAR(50) NOT NULL,
--     rfc       CHAR(13) UNIQUE,
-- 
--     PRIMARY KEY(rfc)
-- );
-- 
-- CREATE TABLE IF NOT EXISTS uruapan_store.address(
--     address_id  INT UNIQUE AUTO_INCREMENT,
--     street      VARCHAR(200) NOT NULL,
--     house_num   VARCHAR(10) NOT NULL,
--     state       VARCHAR(200) NOT NULL,
--     postal_code CHAR(5) NOT NULL,
--     client      CHAR(13) NOT NULL UNIQUE,
-- 
--     FOREIGN KEY(client) REFERENCES client(rfc)
-- );
-- 
-- CREATE TABLE IF NOT EXISTS uruapan_store.store(
--     store_id INT UNIQUE AUTO_INCREMENT,
--     host        VARCHAR(15),
--     db_name  VARCHAR(100) UNIQUE
-- );


-- Sucursal patzcuaro
-- CREATE DATABASE IF NOT EXISTS patzcuaro_store;
-- 
-- CREATE TABLE IF NOT EXISTS patzcuaro_store.client(
--     client_id INT AUTO_INCREMENT UNIQUE,
--     name      VARCHAR(100) NOT NULL,
--     flname    VARCHAR(50) NOT NULL,
--     mlname    VARCHAR(50) NOT NULL,
--     rfc       CHAR(13) UNIQUE,
-- 
--     PRIMARY KEY(rfc)
-- );
-- 
-- CREATE TABLE IF NOT EXISTS patzcuaro_store.address(
--     address_id  INT UNIQUE AUTO_INCREMENT,
--     street      VARCHAR(200) NOT NULL,
--     house_num   VARCHAR(10) NOT NULL,
--     state       VARCHAR(200) NOT NULL,
--     postal_code CHAR(5) NOT NULL,
--     client      CHAR(13) NOT NULL UNIQUE,
-- 
--     FOREIGN KEY(client) REFERENCES client(rfc)
-- );
-- 
-- CREATE TABLE IF NOT EXISTS patzcuaro_store.store(
--     store_id INT UNIQUE AUTO_INCREMENT,
--     host        VARCHAR(15),
--     db_name  VARCHAR(100) UNIQUE
-- );


-- Sucursal cuitzeo_store
-- CREATE DATABASE IF NOT EXISTS cuitzeo_store;
-- 
-- CREATE TABLE IF NOT EXISTS cuitzeo_store.client(
--     client_id INT AUTO_INCREMENT UNIQUE,
--     name      VARCHAR(100) NOT NULL,
--     flname    VARCHAR(50) NOT NULL,
--     mlname    VARCHAR(50) NOT NULL,
--     rfc       CHAR(13) UNIQUE,
-- 
--     PRIMARY KEY(rfc)
-- );
-- 
-- CREATE TABLE IF NOT EXISTS cuitzeo_store.address(
--     address_id  INT UNIQUE AUTO_INCREMENT,
--     street      VARCHAR(200) NOT NULL,
--     house_num   VARCHAR(10) NOT NULL,
--     state       VARCHAR(200) NOT NULL,
--     postal_code CHAR(5) NOT NULL,
--     client      CHAR(13) NOT NULL UNIQUE,
-- 
--     FOREIGN KEY(client) REFERENCES client(rfc)
-- );
-- 
-- CREATE TABLE IF NOT EXISTS cuitzeo_store.store(
--     store_id INT UNIQUE AUTO_INCREMENT,
--     host        VARCHAR(15),
--     db_name  VARCHAR(100) UNIQUE
-- );
