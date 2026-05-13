CREATE SCHEMA DATACENTER;
SET search_path TO datacenter;

---------------------------------------------------------
-- TABLA: Tipo_tarjeta
---------------------------------------------------------
CREATE TABLE Tipo_tarjeta (
    nombre          VARCHAR(50) PRIMARY KEY,
    stock           INT NOT NULL,
    precio_tarjeta  REAL NOT NULL
);

---------------------------------------------------------
-- TABLA: Stock
---------------------------------------------------------
CREATE TABLE Stock (
    tarjeta VARCHAR(50),
    stock   INT,
    PRIMARY KEY (tarjeta, stock),
    FOREIGN KEY (tarjeta) REFERENCES Tipo_tarjeta(nombre)
);

---------------------------------------------------------
-- TABLA: Pasillo
---------------------------------------------------------
CREATE TABLE Pasillo (
    n_pasillo INT PRIMARY KEY
);

---------------------------------------------------------
-- TABLA: Armario
---------------------------------------------------------
CREATE TABLE Armario (
    codigo      VARCHAR(50) PRIMARY KEY,
    n_pasillo   INT NOT NULL,
    pasillo     INT,
    FOREIGN KEY (pasillo) REFERENCES Pasillo(n_pasillo)
);

---------------------------------------------------------
-- TABLA: Tarjeta
---------------------------------------------------------
CREATE TABLE Tarjeta (
    codigo       VARCHAR(50) PRIMARY KEY,
    fila         INT NOT NULL,
    columna      INT NOT NULL,
    descripcion  VARCHAR(200) NOT NULL,
    tipo         VARCHAR(50),
    armario      VARCHAR(50),
    FOREIGN KEY (tipo) REFERENCES Tipo_tarjeta(nombre),
    FOREIGN KEY (armario) REFERENCES Armario(codigo)
);

---------------------------------------------------------
-- TABLA: Robot
---------------------------------------------------------
CREATE TABLE Robot (
    cod_rob   VARCHAR(50) PRIMARY KEY,
    estado    VARCHAR(20) NOT NULL,
    tarjeta   VARCHAR(50),
    pasillo   INT NOT NULL,
    FOREIGN KEY (tarjeta) REFERENCES Tarjeta(codigo),
    FOREIGN KEY (pasillo) REFERENCES Pasillo(n_pasillo),
    CHECK (estado IN ('funcionando', 'parado'))
);

---------------------------------------------------------
-- TABLA: Operario
---------------------------------------------------------
CREATE TABLE Operario (
    codigo    VARCHAR(50) PRIMARY KEY,
    nombre    VARCHAR(100) NOT NULL,
    telefono  VARCHAR(30) NOT NULL,
    pasillo   INT,
    FOREIGN KEY (pasillo) REFERENCES Pasillo(n_pasillo)
);

---------------------------------------------------------
-- TABLA: Reemplazo
---------------------------------------------------------
CREATE TABLE Reemplazo (
    tarjeta       VARCHAR(50) PRIMARY KEY,
    robot         VARCHAR(50) NOT NULL,
    descripcion   VARCHAR(200) NOT NULL,
    fecha_inicio  TIMESTAMP NOT NULL,
    fecha_fin     TIMESTAMP NOT NULL,
    FOREIGN KEY (tarjeta) REFERENCES Tarjeta(codigo),
    FOREIGN KEY (robot) REFERENCES Robot(cod_rob),
    CHECK (fecha_fin > fecha_inicio)
);

-- REPASANDO EL ESQUEMA NOS DIMOS CUENTA DE VARIOS ERRORES Y 
--TUVIMOS QUE AÑADIR ESTAS LINEAS Y MODIFICAMOS ALGUNOS PARAMETROS

--ALTER TABLE Operario
--DROP COLUMN pasillo;

--ALTER TABLE Operario
--DROP CONSTRAINT operario_pasillo_fkey;

--ALTER TABLE Tarjeta
--ALTER COLUMN tipo SET NOT NULL;

--ALTER TABLE Pasillo
--ADD COLUMN operario VARCHAR(50);

--ALTER TABLE Pasillo
--ADD CONSTRAINT pasillo_operario_fkey
--FOREIGN KEY (operario) REFERENCES Operario(codigo);
