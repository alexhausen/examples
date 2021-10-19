@singledispatch
def __get_numbers_only(self, value):
# o metodo anterior nao funcionava, por enquanto vai strip_punctuation até achar coisa melhor
return value


############


def get_funcionario_chave_externa_map():
    """
    OK, eu sei que isso é tosco, mas tenho que achar uma forma de customizar o
    mapeamento, mas a gente chega lá. Primeiro tenho que executar a atualização
    """
    m = get_funcionario_map()
    m[2]["join_field"] = [
        FieldMap(src="PessoaJuridica.chave_externa", dst="chave_externa", op="eq")
    ]
    return m


############


maps = {
    "funcionario": get_funcionario_map,
    "empresa": get_empresa_map,
    "desligados": get_funcionario_chave_externa_map,
    # isso aqui é gambiarra, nao pode ficar amarrado com o nome da interface do arquivo
    "desligados-v2": get_funcionario_chave_externa_map,
}

