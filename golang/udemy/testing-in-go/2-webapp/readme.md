go test ./...
go test -cover ./...
go test -v -tags=integration ./...

docker-compose up -d
go run ./cmd/web/

docker run -it postgres:14.5 bash
root@8520ca12a494:/# psql --host=172.17.0.1 --dbname=users --username=postgres

users=# select * from users;
