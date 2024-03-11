#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <tlm.h>
#include <systemc.h>

template <unsigned int SIZE = 1024>
class memory : public sc_module, tlm::tlm_fw_transport_if<>
{
    private: 

    unsigned char *mem;     

    public: 

    tlm::tlm_target_socket<> tSocket;

    memory(sc_module_name name)
        : sc_module(name), tSocket("target socket`")
    {
        tSocket.bind(*this);
        mem = new unsigned char[SIZE];
    }

    ~memory()
    {
        free(mem);
    }

    SC_HAS_PROCESS(memory);

    void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay)
    {
        if(trans.get_address() >= SIZE)
        {
            SC_REPORT_FATAL(this->name(),"Address out of range!!!");
            return;
        }

        if(trans.get_command() == tlm::TLM_WRITE_COMMAND)
        {            
            memcpy(
                &mem[trans.get_address()],
                trans.get_data_ptr(),
                trans.get_data_length()
            );
        }
        else // (trans.get_command() == tlm::TLM_READ_COMMAND)
        {
            memcpy(
                trans.get_data_ptr(),
                &mem[trans.get_address()],
                trans.get_data_length()
            );
        }

        delay = delay + sc_time(20, SC_NS);

        trans.set_response_status( tlm::TLM_OK_RESPONSE );
    }

    // stubs
    tlm::tlm_sync_enum nb_transport_fw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay )
    {
        SC_REPORT_FATAL(this->name(),"nb_transport_fw is not implemented");
        return tlm::TLM_ACCEPTED;
    }

    // stubs
    bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                            tlm::tlm_dmi& dmi_data)
    {
        SC_REPORT_FATAL(this->name(),"get_direct_mem_ptr is not implemented");
        return false;
    }

    // stubs
    unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
    {
        SC_REPORT_FATAL(this->name(),"transport_dbg is not implemented");
        return 0;
    }
};

#endif // MEMORY_H
