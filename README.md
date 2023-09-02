# TP01-getprocessinfo_nanvix
Implementa no Nanvix uma chamada de sistema que coloca em um buffer informações de um processo indicado pelo seu PID.

Integrantes do grupo:

* Rafael Ramos -> Gerência do Projeto, criação do programa utilitário e correção de bugs.
* Marcus Leandro -> Criação da função que busca na tabela de processos o processo com o PID solicitado.
* Arthur Lanna -> Criação da função Trap responsável pela troca de contexto, modo usuário para modo Kernel.
* Samuel Rocha -> Criação da chamada de sistema resposável por chamar a função que busca o processo.
