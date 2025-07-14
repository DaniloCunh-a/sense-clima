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
    
    // Para o estado SLP1, a UART pode permanecer ativa se configurada para wakeup.
    // Para modos de sono mais profundos, você precisaria desinicializá-la aqui.
    
    // Configura o timer AON (Always-On) como a fonte de wakeup.
    // slpManAonTimerStart(sleep_ms);
    slpManDeepSlpTimerStart(DEEPSLP_TIMER_ID7, sleep_ms);

    // Entra no estado de sono especificado. A MCU irá parar aqui até um evento de wakeup.
    // slpManEnterSlp(state);
    slpManSetPmuSleepMode(true, state, false);

    // --- A execução continua aqui após o wakeup ---

    // O timer AON é um timer "one-shot" e é parado automaticamente no wakeup.

    // Ao acordar do SLP1, o estado do core é mantido, mas alguns clocks podem precisar
    // ser restaurados. O código de inicialização (BSP) cuida do básico.
    // Pode ser necessário reinicializar a UART usada para o printf.
    extern USART_HandleTypeDef huart1;
    uint32_t uart_cntrl = (ARM_USART_MODE_ASYNCHRONOUS | ARM_USART_DATA_BITS_8 | ARM_USART_PARITY_NONE | 
                           ARM_USART_STOP_BITS_1 | ARM_USART_FLOW_CONTROL_NONE);
    HAL_USART_InitPrint(&huart1, GPR_UART1ClkSel_26M, uart_cntrl, 115200);
}
/************************ HT Micron Semicondutores S.A *****END OF FILE****/
