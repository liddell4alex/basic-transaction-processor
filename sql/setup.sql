-- Sucursal morelia
CREATE DATABASE IF NOT EXISTS morelia_store;

CREATE TABLE IF NOT EXISTS morelia_store.client(
    client_id INT AUTO_INCREMENT,
    name      VARCHAR(100) NOT NULL,
    flname    VARCHAR(50) NOT NULL,
    mlname    VARCHAR(50),
    rfc       CHAR(13) UNIQUE,

    PRIMARY KEY(client_id)
);

CREATE TABLE IF NOT EXISTS morelia_store.address(
    address_id  INT UNIQUE AUTO_INCREMENT,
    street      VARCHAR(200) NOT NULL,
    house_num   VARCHAR(5) NOT NULL,
    state       VARCHAR(200) NOT NULL,
    postal_code CHAR(5) NOT NULL,
    client      INT,

    FOREIGN KEY(client) REFERENCES client(client_id)
);

CREATE TABLE IF NOT EXISTS morelia_store.store(
    store_id INT UNIQUE AUTO_INCREMENT,
    host        VARCHAR(15),
    db_name  VARCHAR(100) UNIQUE
);


-- Sucursal patzcuaro
CREATE DATABASE IF NOT EXISTS patzcuaro_store;

CREATE TABLE IF NOT EXISTS patzcuaro_store.client(
    client_id INT AUTO_INCREMENT,
    name      VARCHAR(100) NOT NULL,
    flname    VARCHAR(50) NOT NULL,
    mlname    VARCHAR(50),
    rfc       CHAR(13) UNIQUE,

    PRIMARY KEY(client_id)
);

CREATE TABLE IF NOT EXISTS patzcuaro_store.address(
    address_id  INT UNIQUE AUTO_INCREMENT,
    street      VARCHAR(200) NOT NULL,
    house_num   VARCHAR(5) NOT NULL,
    state       VARCHAR(200) NOT NULL,
    postal_code CHAR(5) NOT NULL,
    client      INT,

    FOREIGN KEY(client) REFERENCES client(client_id)
);

CREATE TABLE IF NOT EXISTS patzcuaro_store.store(
    store_id INT UNIQUE AUTO_INCREMENT,
    host        VARCHAR(15),
    db_name  VARCHAR(100) UNIQUE
);

-- Sucursal uruapan
CREATE DATABASE IF NOT EXISTS uruapan_store;

CREATE TABLE IF NOT EXISTS uruapan_store.client(
    client_id INT AUTO_INCREMENT,
    name      VARCHAR(100) NOT NULL,
    flname    VARCHAR(50) NOT NULL,
    mlname    VARCHAR(50),
    rfc       CHAR(13) UNIQUE,

    PRIMARY KEY(client_id)
);

CREATE TABLE IF NOT EXISTS uruapan_store.address(
    address_id  INT UNIQUE AUTO_INCREMENT,
    street      VARCHAR(200) NOT NULL,
    house_num   VARCHAR(5) NOT NULL,
    state       VARCHAR(200) NOT NULL,
    postal_code CHAR(5) NOT NULL,
    client      INT,

    FOREIGN KEY(client) REFERENCES client(client_id)
);

CREATE TABLE IF NOT EXISTS uruapan_store.store(
    store_id INT UNIQUE AUTO_INCREMENT,
    host        VARCHAR(15),
    db_name  VARCHAR(100) UNIQUE
);

-- Sucursal napa
CREATE DATABASE IF NOT EXISTS napa_store;

CREATE TABLE IF NOT EXISTS napa_store.client(
    client_id INT AUTO_INCREMENT,
    name      VARCHAR(100) NOT NULL,
    flname    VARCHAR(50) NOT NULL,
    mlname    VARCHAR(50),
    rfc       CHAR(13) UNIQUE,

    PRIMARY KEY(client_id)
);

CREATE TABLE IF NOT EXISTS napa_store.address(
    address_id  INT UNIQUE AUTO_INCREMENT,
    street      VARCHAR(200) NOT NULL,
    house_num   VARCHAR(5) NOT NULL,
    state       VARCHAR(200) NOT NULL,
    postal_code CHAR(5) NOT NULL,
    client      INT,

    FOREIGN KEY(client) REFERENCES client(client_id)
);

CREATE TABLE IF NOT EXISTS napa_store.store(
    store_id INT UNIQUE AUTO_INCREMENT,
    host        VARCHAR(15),
    db_name  VARCHAR(100) UNIQUE
);
