# python 3
# método para validar e formatar valores dos campos

import traceback

#class "QualquerCoisa":
    # ... 200 linhas depois
    def formatter(self, idx, field_name, field_data, value, fmts):
        if fmts and value is not None:
            f = fmts.pop(0)
            if not fmts and field_data:
                f = (f, field_data)
            level = None
            try:
                return (
                    self.formatter(
                        idx, field_name, field_data, f[0](value, **f[1]), fmts
                    )
                    if isinstance(f, (list, tuple))
                    else self.formatter(idx, field_name, field_data, f(value), fmts)
                )
            except Exception as e:
                # isso aqui é um SEMI-POG: metodo mais simples para determinar o nivel de recursao
                # o -12 é o nivel de frames atual, ISSO PODE MUDAR SE MUDAR O CODIGO!
                level = len(getouterframes(currentframe())) - 12
                if level == 0:
                    self.logger.warning(
                        "{}: Dado inválido: {}: {}. Valor = '{}';".format(
                            idx, field_name.upper(), e, value
                        )
                    )
                self.logger.debug("{}: \n{}".format(idx, traceback.format_exc()))
                if not self.fields[field_name].optional:
                    raise e
        else:
            return value

