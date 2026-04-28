#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*------------------------------------------BIT REGISTERS------------------------------------------------*/

#define REG_SIZE 8


#define WRITE_BIT(REG,BIT,LOGIC) ( (LOGIC>0) ? (REG |= (1<<BIT)) : (REG &=~ (1<<BIT)) )

#define SET_BIT(REG,BIT) ( REG |= (1<<BIT) )
#define CLEAR_BIT(REG,BIT) ( REG &=~ (1<<BIT) )
#define TOGGLE_BIT(REG,BIT) ( REG ^= (1<<BIT) )

#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )
#define GET_BIT(REG,BIT) ( (REG & (1<<BIT)) >> BIT )

#define SHIFT_LEFT(REG,NUM) ( REG = REG<<NUM )
#define SHIFT_RIGHT(REG,NUM) ( REG = REG>>NUM )
#define ROTATE_LEFT(REG,NUM) ( REG = (REG<<NUM) | (REG>>(REG_SIZE-NUM)) )
#define ROTATE_RIGHT(REG,NUM) ( REG = (REG>>NUM) | (REG<<(REG_SIZE-NUM)) )


#endif /* COMMON_MACROS_H_ */
