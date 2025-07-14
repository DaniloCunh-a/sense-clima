/**
 *
 * Copyright (c) 2023 HT Micron Semicondutores S.A.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "HT_Sleep.h"
#include "slpman_qcx212.h"
#include "htnb32lxxx_hal_usart.h"
#include "debug_log.h"

// Esta é uma função de sleep simplificada. Em um cenário real,
// você precisaria gerenciar cuidadosamente quais periféricos desinicializar
// antes de dormir e reinicializar ao acordar para economizar o máximo de energia.

void HT_Sleep_EnterSleep(slpManSlpState_t state, uint32_t sleep_ms) {
    
    // Garante que todas as mensagens de log pendentes sejam enviadas antes de dormir
    uniLogFlushOut(0);
    
    if (state == SLP_SLP2_STATE) {
        // Configura o timer de sono profundo (Deep Sleep Timer) como a fonte de wakeup.
        slpManDeepSlpTimerStart(DEEPSLP_TIMER_ID7, sleep_ms);

        // Entra no modo de sono profundo. A execução para aqui.
        // O dispositivo será reiniciado pelo hardware ao acordar.
        slpManSetPmuSleepMode(true, state, false);

        // O CÓDIGO ABAIXO NUNCA SERÁ ALCANÇADO NO MODO SLP2,
        // POIS O SISTEMA REINICIA.
    } else {
        // Lógica para outros modos de sono (ex: SLP1) pode ser adicionada aqui.
        printf("Unsupported sleep state for this implementation.\n");
    }
}
/************************ HT Micron Semicondutores S.A *****END OF FILE****/
