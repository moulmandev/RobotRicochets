SET default_storage_engine= InnoDB;
SET GLOBAL log_bin_trust_function_creators = 1;

drop table if exists Player;

/*==============================================================*/
/* Table : User                                             */
/*==============================================================*/
create table Users
(
   idUsers	int not null auto_increment,
   login	varchar(255),
   passwd	varchar(255),
   
   primary key (idUsers)
);

