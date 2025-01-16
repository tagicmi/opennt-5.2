struct HWID {
	union {
		unsigned __int64 AsQword;
		struct {
			// dword 1
			unsigned volume_serial:10;
			unsigned network_mac:10;
			unsigned cdrom_id:7;
			unsigned display_id:5;
			// dword 2
			unsigned ver:3;
			unsigned cpu_serial:6;
			unsigned disk_id:7;
			unsigned scsi_adapter_id:5;
			unsigned hdc_id:4;
			unsigned cpu_model:3;
			unsigned mem:3;
			unsigned dockable:1;
		};
	};
};
extern void sub_105AB66(HWID* arg_0);
extern BOOL sub_105ACAD(HWID* arg_0);
