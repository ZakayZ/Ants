//
// Created by Artem Novikov on 15.09.2022.
//

#include "AntState.h"

AntState::AntState(MovementData& ant_move, const GeneralData& ant_general)
    : move_data_(ant_move), general_data_(ant_general), change_state_(StateType::None) {}

AntState::~AntState() = default;
