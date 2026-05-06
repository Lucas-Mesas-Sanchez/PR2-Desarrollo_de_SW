---------------------------------------------------------
-- Tipo_tarjeta (NICs reales)
---------------------------------------------------------
INSERT INTO Tipo_tarjeta VALUES ('Intel_X520', 40, 180.0);
INSERT INTO Tipo_tarjeta VALUES ('Mellanox_CX4', 25, 350.0);
INSERT INTO Tipo_tarjeta VALUES ('Broadcom_57414', 30, 290.0);
INSERT INTO Tipo_tarjeta VALUES ('Intel_X710', 50, 220.0);
INSERT INTO Tipo_tarjeta VALUES ('Mellanox_CX5', 20, 480.0);
INSERT INTO Tipo_tarjeta VALUES ('Broadcom_57810', 35, 260.0);
INSERT INTO Tipo_tarjeta VALUES ('Intel_E810', 15, 650.0);

---------------------------------------------------------
-- Stock
---------------------------------------------------------
INSERT INTO Stock VALUES ('Intel_X520', 40);
INSERT INTO Stock VALUES ('Mellanox_CX4', 25);
INSERT INTO Stock VALUES ('Broadcom_57414', 30);
INSERT INTO Stock VALUES ('Intel_X710', 50);
INSERT INTO Stock VALUES ('Mellanox_CX5', 20);
INSERT INTO Stock VALUES ('Broadcom_57810', 35);
INSERT INTO Stock VALUES ('Intel_E810', 15);

---------------------------------------------------------
-- Pasillo (tus pasillos originales)
---------------------------------------------------------
INSERT INTO Pasillo VALUES (1);
INSERT INTO Pasillo VALUES (2);
INSERT INTO Pasillo VALUES (3);

---------------------------------------------------------
-- Armario (racks por pasillo)
---------------------------------------------------------
INSERT INTO Armario VALUES ('RACK1-A', 1, 1);
INSERT INTO Armario VALUES ('RACK1-B', 2, 1);
INSERT INTO Armario VALUES ('RACK2-A', 3, 2);
INSERT INTO Armario VALUES ('RACK2-B', 4, 2);
INSERT INTO Armario VALUES ('RACK3-A', 5, 3);
INSERT INTO Armario VALUES ('RACK3-B', 6, 3);

---------------------------------------------------------
-- Tarjeta (20 NICs instaladas en racks)
---------------------------------------------------------
INSERT INTO Tarjeta VALUES ('NIC001',1,1,'Intel X520 en Dell R740','Intel_X520','RACK1-A');
INSERT INTO Tarjeta VALUES ('NIC002',1,2,'Mellanox CX4 en HP DL380','Mellanox_CX4','RACK1-A');
INSERT INTO Tarjeta VALUES ('NIC003',2,1,'Broadcom 57414 en Lenovo SR650','Broadcom_57414','RACK1-B');
INSERT INTO Tarjeta VALUES ('NIC004',2,2,'Intel X710 en Dell R640','Intel_X710','RACK1-B');
INSERT INTO Tarjeta VALUES ('NIC005',3,1,'Mellanox CX5 100GbE en nodo GPU','Mellanox_CX5','RACK2-A');
INSERT INTO Tarjeta VALUES ('NIC006',3,2,'Broadcom 57810 10GbE','Broadcom_57810','RACK2-A');
INSERT INTO Tarjeta VALUES ('NIC007',4,1,'Intel E810 100GbE','Intel_E810','RACK2-B');
INSERT INTO Tarjeta VALUES ('NIC008',4,2,'Intel X520 en servidor backup','Intel_X520','RACK2-B');
INSERT INTO Tarjeta VALUES ('NIC009',5,1,'Mellanox CX4 en nodo Ceph','Mellanox_CX4','RACK3-A');
INSERT INTO Tarjeta VALUES ('NIC010',5,2,'Intel X710 en nodo Ceph','Intel_X710','RACK3-A');
INSERT INTO Tarjeta VALUES ('NIC011',6,1,'Broadcom 57414 en servidor virtualización','Broadcom_57414','RACK3-B');
INSERT INTO Tarjeta VALUES ('NIC012',6,2,'Intel X520 en servidor virtualización','Intel_X520','RACK3-B');
INSERT INTO Tarjeta VALUES ('NIC013',1,3,'Mellanox CX5 en nodo IA','Mellanox_CX5','RACK1-A');
INSERT INTO Tarjeta VALUES ('NIC014',2,3,'Intel E810 en nodo IA','Intel_E810','RACK1-B');
INSERT INTO Tarjeta VALUES ('NIC015',3,3,'Broadcom 57810 en servidor web','Broadcom_57810','RACK2-A');
INSERT INTO Tarjeta VALUES ('NIC016',4,3,'Intel X710 en servidor web','Intel_X710','RACK2-B');
INSERT INTO Tarjeta VALUES ('NIC017',5,3,'Intel X520 en servidor logs','Intel_X520','RACK3-A');
INSERT INTO Tarjeta VALUES ('NIC018',6,3,'Mellanox CX4 en servidor logs','Mellanox_CX4','RACK3-B');
INSERT INTO Tarjeta VALUES ('NIC019',1,4,'Broadcom 57414 en servidor BD','Broadcom_57414','RACK1-A');
INSERT INTO Tarjeta VALUES ('NIC020',2,4,'Intel E810 en servidor BD','Intel_E810','RACK1-B');

---------------------------------------------------------
-- Robot (robots de mantenimiento)
---------------------------------------------------------
INSERT INTO Robot VALUES ('RBOT01','funcionando','NIC001',1);
INSERT INTO Robot VALUES ('RBOT02','parado','NIC005',2);
INSERT INTO Robot VALUES ('RBOT03','funcionando',NULL,3);
INSERT INTO Robot VALUES ('RBOT04','funcionando','NIC010',1);
INSERT INTO Robot VALUES ('RBOT05','parado',NULL,2);

---------------------------------------------------------
-- Operario (tus operarios originales)
---------------------------------------------------------
INSERT INTO Operario VALUES ('OP01','Carlos Ruiz','600123123',1);
INSERT INTO Operario VALUES ('OP02','Ana Torres','611222333',2);
INSERT INTO Operario VALUES ('OP03','Luis Pérez','622333444',3);

---------------------------------------------------------
-- Reemplazo (con TIMESTAMP: día, mes, año, hora, minutos)
---------------------------------------------------------
INSERT INTO Reemplazo VALUES
('NIC003','RBOT01','Fallo en puerto 10GbE',
 '2024-01-10 08:30','2024-01-12 08:35');

INSERT INTO Reemplazo VALUES
('NIC006','RBOT02','Temperatura excesiva en NIC',
 '2024-02-05 10:00','2024-02-06 10:04');

INSERT INTO Reemplazo VALUES
('NIC011','RBOT04','Pérdida de enlace intermitente',
 '2024-03-01 09:15','2024-03-03 09:17');

INSERT INTO Reemplazo VALUES
('NIC017','RBOT03','Sustitución preventiva',
 '2024-03-10 11:00','2024-03-11 11:05');

INSERT INTO Reemplazo VALUES
('NIC019','RBOT05','Fallo en módulo óptico',
 '2024-04-01 07:50','2024-04-04 7:53');