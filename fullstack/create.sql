drop table card;
drop table board_column;
drop table board;

create table board (
    id_board serial primary key,
    name text
);

create table board_column (
    id_board_column serial primary key,
    id_board integer references board (id_board),
    name text,
    has_estimate boolean
);

create table card (
    id_card serial primary key,
    id_board_column integer references board_column (id_board_column),
    title text,
    estimate integer
);

insert into board (id_board, name) values (1, 'Projeto 1');
insert into board_column (id_board_column, id_board, name, has_estimate) values (1, 1, 'Coluna A', true);
insert into board_column (id_board_column, id_board, name, has_estimate) values (2, 1, 'Coluna B', true);
insert into board_column (id_board_column, id_board, name, has_estimate) values (3, 1, 'Coluna C', true);
insert into card (id_card, id_board_column, title, estimate) values (1, 1, 'Atividade 1', 3);
insert into card (id_card, id_board_column, title, estimate) values (2, 1, 'Atividade 2', 2);
insert into card (id_card, id_board_column, title, estimate) values (3, 1, 'Atividade 3', 1);

/*
select * from board
join board_column on board_column.id_board = board.id_board
join card on card.id_board_column = board_column.id_board_column
*/
