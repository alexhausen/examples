# Refatoração (Martin Fowler) - Capítulo 4: Escrevendo Testes

## Antes de iniciar

> Lembre-se esse não é um livro sobre testes

Nota: e que diferentes autores usam definições diferentes

O foco do capítulo é nos testes de unidade.

Testes de outros tipos (desempenho/segurança) ou em outros níveis (sistema/integração) não são tratados aqui.

## Introdução

Para refatorar de forma apropriada é preciso ter uma suíte de testes robusta.

A refatoração exige testes. Se quiser refatorar, você deve escrever testes.

É contraintuitivo, mas escrever bons testes aumenta a eficiência do programador (explicação na próxima seção)

## Importância do código autotestável

Codificar é uma pequena parte do trabalho
- descobrir (o problema)
- design (ie. projetar a solução)
- debug (é a maior parte do trabalho)

Corrigir o _bug_ é rápido, mas encontrá-lo é demorado

O autor começa a pensar em "código auto-testável" em '92 em uma palestra que dizia "as classes deveriam conter seus próprios testes".

1. juntou desenvolvimento iterativo + testes manuais a cada iteração = :)

2. dev iterativo + testes automáticos = XD

> Garanta que os testes sejam totalmente automatizados e que verifiquem os próprios resultados.

Vantagens observadas:
- fácil de executar
- rápido de obter o resultado
- identificação de um _bug_ no código novo (se um teste falhar)
- correção rápida (pois antes funcionava e o código novo está fresco na memória)

Isso fez o autor gostar de adicionar mais testes, mesmo antes de terminar a iteração

> Uma suíte de testes é um detector de bugs eficaz, que reduz o tempo necessário para encontrar bugs.

Origem e influência do JUnit Kent Beck e Erich Gamma '97

Barreiras:
- escrever (muito) mais código
- as pessoas não aprenderam a escrever testes
- não tem a vivência de como isso ajudo

Recomendação: TDD (_Test Driven Development_ - Desenvolvimento Orientado a Testes)
1. escrever um teste que falha
2. escrever o código para passar teste
3. refatorar
4. repete

## Código exemplo

> Um código sem testes é apresentado e o autor escreve os testes para esse código. Após esses testes o código poderá ser refatorado.

App web com entradas numéricas e atualização automática dos resultados de:
1. _shortfall_ (défict na produção = demanda - produção total)
2. _profit_ (lucro)

[class Province 1 - construtor]

[dados para teste]

[class Province 2 - getters/setters]

[class Producer - construtor, getters/setters]

[class Province - shortfall]

[class Province - profit]

> Código é "feio" e "fedorento", mas ainda não é hora de refatorar.

## Teste inicial

Exemplo do livro usa os _frameworks_ Mocha e Chai.

[teste simples]

Separar o código de teste em blocos "it" agrupados em suítes ("describe")

Os dois passos do exemplo:
1. define _fixtures_ (ie. dados necessários ao teste)
2. verifica as características da _fixture_

Obs.: o autor prefere usar descrições curtas para os argumentos "describe" e "it", mas reconhece que outras pessoas preferem frases mais explicativas e alerta para que o risco que aconteça o que pode acontecer com comentários desatualizados.

> Sempre garanta que um teste falhará quando deve falhar.

Dica do autor: modificar temporariamente o código da aplicação para demonstrar que o teste falha quando deve (e no lugar certo).

> Execute testes frequentemente. Execute os testes que exercitam o código com o qual você está trabalhando, pelo menos com um intervalo de alguns minutos; execute todos os testes no mínimo uma vez por dia.

Uso _assert_ X _expect_: a depender do _framework_

Alerta para nunca refatorar se algum teste estiver falhando.

## Acrescente outro teste

O autor sugere observar tudo que a classe deveria fazer e testar cada um desses aspectos, em quaisquer condições que possam fazer a classe falhar.

Os testes devem ser orientados a riscos; lembre-se de que estou **tentando encontrar bugs**. Desnecessário testar métodos triviais.

Não adianta escrever muitos testes que não vão encontrar erro nenhum.

Foco: testar as partes mais preocupantes,

[teste profit]

Refatoração para retirar o código duplicado

[exemplo de como não fazer]

[exemplo usando o beforeEach]

Vantagem de usar o beforeEach: determinismo e remoção da duplicação

## Modificando o _fixture_

O autor modifica a configuração da _fixture_ padrão para exercitar outras possibilidades e depois verificar o resultado.

Isso é conhecido como:
- _setup-exercise-verify_; ou
- _given-when-then_; ou
- _arrange-act-assert_.

A configuração é feita no beforeEach, beforeAll, setUp.
As vezes é necessário "resetar" o estado da aplicação ou liberar recursos com uma fase de _teardown_.

O autor recomenda fazer um teste por bloco: o exemplo faz duas verificações (expect) no mesmo bloco. Apesar disso, o autor considera como um único teste pois as verificações estão muito ligadas.

## Sondando os limites

Até agora testamos apenas o "caminho feliz" (_happy path_)

O autor sugere alguns critérios de teste úteis para teste das condições limites:
- lista vazia: []
- string vazia: ""
- entradas nulas (undefined)
- valor zero
- valor negativo

> Pense nas condições limites nas quais algo pode dar errado e concentre aí seus testes.

O autor faz uma discussão sobre o sentido de ter lucro negativo no domínio da aplicação. Se o valor retornado deveria ser zero ou gerar algum tipo de erro.

[exemplo com demand=""]

[exemplo com producers=""]

Diferença entre "falhas" e "erros", exemplo: "undefined is not a function".

Razões para não validar a entrada (e portanto não fazer esse tipo de teste): código confiável, da mesma base ou já sanitizado, evitar verificações duplicadas em vários lugares.
Razões para validar a entrada: código externo, entrada não confiável.

Lembre-se: "A refatoração deve preservar o comportamento observável"

<Treta alert>

Se um erro (como o do exemplo) não é parte do comportamento observável então não faremos um teste para ele **antes** de refatorar.

Se um erro levar puder causar uma falha posso usar a refatoração "Introduzir asserção" (que é colocar um assert no código de aplicação).

### Quando parar?

"É impossível provar por meio de testes que um programa não tenha _bugs_".

Não tente "testar tudo". Concentre-se nos pontos de risco, código complexo, áreas mais prováveis de haver falhas.

> Não deixe que o medo de os testes não capturarem todos os bugs impeça você de escrever testes que capturem a maioria dos bugs.

## Muito além disso

A importância do teste vai para além da refatoração.

Evolução da percepção dos testes pelos desenvolvedores.

A arquitetura pode ser julgada pela testabilidade

Os testes existentes também devem ser mantidos e refatorados.

Dica do autor:
> Ao receber o relatório de um bug, comece escrevendo um teste de unidade que exponha o _bug_.

### Quantos testes são suficientes?

Não há resposta objetiva.

A cobertura pode ajudar a identificar áreas pouco testadas, mas não para avaliar a **qualidade** de uma suíte de testes.

A melhor medida é a sua confiança que os testes vão identificar alguma falha se o código for modificado.

É possível ter testes demais? Sim, um sinal é se a cada modificação do código da aplicação você gasta muito mais tempo modificando os testes existentes. Mas (segundo o autor) isso é muito raro; o normal é ter menos testes do que o necessário.

