#ifndef PACKETID_H
#define PACKETID_H

#include <QObject>

class PacketId
{
public:
    static const quint32 CERTIFY_LOGIN;
    static const quint32 INSTANT_LOGIN;
    static const quint32 INSTANT_EXIT;
    static const quint32 CERTIFY_EXIT;
    static const quint32 CHARACTER_INFO;
    static const quint32 CREATE_CHARACTER;
    static const quint32 CHOICE_CHARACTER;
    static const quint32 REMOVE_CHARACTER;
    static const quint32 SERVER_LIST;
    static const quint32 SERVER_INFO;
    static const quint32 UPGRADE_CHARACTER;
    static const quint32 UPDATE_TUTORIAL;
    static const quint32 GAME_LOGIN;
    static const quint32 GAME_EXIT;
    static const quint32 UDP_CONFIRM;
    static const quint32 PLAYER_INFO;
    static const quint32 ITEM_LIST;
    static const quint32 TRAINING_LIST;
    static const quint32 SKILL_LIST;
    static const quint32 CELEBRATION_LIST;
    static const quint32 FRIENDS_LIST;
    static const quint32 FRIEND_REQUEST;
    static const quint32 FRIEND_RESPONSE;
    static const quint32 DELETE_FRIEND;
    static const quint32 CLUB_INFO;
    static const quint32 CLUB_MEMBERS;
    static const quint32 IGNORED_LIST;
    static const quint32 BLOCK_PLAYER;
    static const quint32 UNBLOCK_PLAYER;
    static const quint32 STATUS_MESSAGE;
    static const quint32 ROOM_LIST;
    static const quint32 CREATE_ROOM;
    static const quint32 JOIN_ROOM;
    static const quint32 QUICK_JOIN_ROOM;
    static const quint32 NEXT_TIP;
    static const quint32 ROOM_INFO;
    static const quint32 ROOM_PLAYER_INFO;
    static const quint32 LEAVE_ROOM;
    static const quint32 ROOM_MASTER;
    static const quint32 SWAP_TEAM;
    static const quint32 ROOM_MAP;
    static const quint32 ROOM_BALL;
    static const quint32 ROOM_SETTINGS;
    static const quint32 KICK_PLAYER;
    static const quint32 LOBBY_LIST;
    static const quint32 INVITE_PLAYER;
    static const quint32 CHAT_MESSAGE;
    static const quint32 SET_OBSERVER;
    static const quint32 START_COUNT_DOWN;
    static const quint32 HOST_INFO;
    static const quint32 COUNT_DOWN;
    static const quint32 CANCEL_COUNT_DOWN;
    static const quint32 MATCH_LOADING;
    static const quint32 PLAYER_READY;
    static const quint32 CANCEL_LOADING;
    static const quint32 START_MATCH;
    static const quint32 MATCH_RESULT;
    static const quint32 MATCH_FORCED_RESULT;
    static const quint32 UNKNOWN1;
    static const quint32 UNKNOWN2;
    static const quint32 UPDATE_ROOM_PLAYER;
    static const quint32 PLAYER_BONUS_STATS;
    static const quint32 PURCHASE_ITEM;
    static const quint32 RESELL_ITEM;
    static const quint32 ACTIVATE_ITEM;
    static const quint32 DEACTIVATE_ITEM;
    static const quint32 MERGE_ITEM;
    static const quint32 PURCHASE_LEARN;
    static const quint32 PURCHASE_SKILL;
    static const quint32 ACTIVATE_SKILL;
    static const quint32 DEACTIVATE_SKILL;
    static const quint32 PURCHASE_CELE;
    static const quint32 ACTIVATE_CELE;
    static const quint32 DEACTIVATE_CELE;
    static const quint32 TCP_PING;
    static const quint32 UPDATE_SETTINGS;
    static const quint32 PLAYER_DETAILS;
    static const quint32 ADD_STATS_POINTS;
    static const quint32 PLAYER_PROGRESS;
    static const quint32 PLAYER_STATS;
    static const quint32 UDP_PING;
    static const quint32 UDP_AUTHENTICATE;
    static const quint32 UDP_GAME_1;
    static const quint32 UDP_GAME_2;
    static const quint32 UDP_GAME_3;
    static const quint32 UDP_GAME_4;
    static const quint32 UDP_GAME_5;
};

#endif // PACKETID_H
