#ifndef IO_VMI_H
#define IO_VMI_H

#include <libvmi/libvmi.h>
#include <libvmi/events.h>
#include <libvmi/libvmi_extra.h>
#include <libvmi/x86.h>
#include <r_debug.h>
#include <glib.h>


typedef struct {
    char *vm_name;
    bool url_identify_by_name;
    char* proc_name;
    int pid;
    uint64_t pid_cr3;
    int current_vcpu;
    vmi_instance_t vmi;
    bool attached;
    vmi_event_t *sstep_event;
    // table [rip] -> [vmi_event_t]
    // event might be int3 or mem_event
    GHashTable *bp_events_table;
    // if we are attaching to a new process being created
    // or if the process is already existing
    bool attach_new_process;
    // if you hit an int3, this will indicate if we need a singlestep
    // because it's the wrong process
    bool int3_need_sstep;
    RBreakpoint *int3_bp;
    RBreakpointItem *int3_bp_item;
    vmi_event_t *int3_event;
} RIOVmi;

typedef struct
{
    RIOVmi *rio_vmi;
    uint64_t pid_cr3;
    addr_t bp_vaddr;
    RBreakpoint* bp;
    RBreakpointItem *bpitem;
} bp_event_data;

#endif // IO_VMI_H
