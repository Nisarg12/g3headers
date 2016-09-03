/**
 * @file
 * @brief Overworld scripting.
 */

#ifndef POKEAGB_OVERWORLD_SCRIPT_H_
#define POKEAGB_OVERWORLD_SCRIPT_H_

#include <pokeagb/common.h>
#include <pokeagb/types.h>

POKEAGB_BEGIN_DECL

struct ScriptEnvironment;

/**
 * @return 0 to indicate succcess, 1 to enter wait state.
 */
typedef u8 (*ScriptCommand)(struct ScriptEnvironment* environment);

/**
 * @return 1 when finished, 0 to keep executing.
 */
typedef u8 (*ScriptFunction)(void);

enum ScriptExecutionMode {
    /** The environment is not executing anything (wait state). */
    SCRIPT_EXECUTE_MODE_PAUSED,

    /** Normal script execution mode. */
    SCRIPT_EXECUTE_MODE_NORMAL,

    /** Executing pointer_asm function. */
    SCRIPT_EXECUTE_MODE_ASM,
};

struct ScriptEnvironment {
    /**
     * Call stack depth.
     */
    u8 depth;

    /**
     * Execution mode.
     */
    enum ScriptExecutionMode mode;

    /**
     * Function to run.
     */
    u8 cmp_result;
    u8 field_3;

    /**
     * Pointer to a function.  Executed when mode ==
     * SCRIPT_EXECUTE_MODE_ASM
     */
    ScriptFunction pointer_asm;

    /**
     * Pointer to a script.  Executed when mode ==
     * SCRIPT_EXECUTE_MODE_NORMAL
     */
    u8* pointer_script;

    /**
     * Call stack.
     */
    u8* stack[20];

    /**
     * Pointer to script commands.  This means we can hot swap
     * scripting commands to implent an ad-hoc custom script engine,
     * like the engine does with mystery gift. */
    ScriptCommand* cmd_table;

    /**
     * Pointer to the last command in the table.
     */
    ScriptCommand* cmd_table_max;

    /**
     * Script banks.  Bank 0 is used for loading a pointer to a message to display.
     */
    u32 vars[4];

    /**
     * Usually set to false during cutscenes.
     */
    bool enabled;
    u8 field_75;

    /**
     * Whether to enable the keypad.  Set to true during signpost
     * scripts so you can walk away to cancel the script.
     */
    u8 keypad_control_enabled;

    /**
     * Locks player movement.
     */
    u8 keypad_override_direction;
};

ASSERT_SIZEOF(struct ScriptEnvironment, 0x78);

/**
 * Primary script environment for regular scripts.
 *
 * @address{BPRE,03000EB0}
 */
extern struct ScriptEnvironment script_env_1;

/**
 * Secondary script environment for level scripts.
 *
 * @address{BPRE,03000F28}
 */
extern struct ScriptEnvironment script_env_2;

/**
 * Start of standard script command table.
 *
 * @address{BPRE,0815F9B4}
 */
extern ScriptCommand* script_cmds;

/**
 * End of standard script command table.
 *
 * @address{BPRE,0815FD08}
 */
extern ScriptCommand* script_cmds_max;

/**
 * Script temporary variable 0x8000
 * @address{BPRE,020375D8}
 */
extern u16 var_8000;

/**
 * Script temporary variable 0x8001
 * @address{BPRE,020375DA}
 */
extern u16 var_8001;

/**
 * Script temporary variable 0x8002
 * @address{BPRE,020375DC}
 */
extern u16 var_8002;

/**
 * Script temporary variable 0x8003
 * @address{BPRE,020375DE}
 */
extern u16 var_8003;

/**
 * Script temporary variable 0x800D
 * @address{BPRE,020375F0}
 */
extern u16 var_800D;

POKEAGB_END_DECL

#endif /* POKEAGB_OVERWORLD_SCRIPT_H_ */
