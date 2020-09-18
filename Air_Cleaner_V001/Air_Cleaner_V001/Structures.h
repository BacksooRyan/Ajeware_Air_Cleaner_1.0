#ifndef _AC_STRUCTURE_HEADER_
#define _AC_STRUCTURE_HEADER_

enum class PlayMode
{
	Auto0 = 0, // ���� ���� �������� ���� �ڵ����� �� �ӵ��� �����Ѵ�.
	Auto1, // 01 ������ ������ 50%
	Auto2, // 03 ������ ������ 50%
	Auto3, // 10 ������ ������ 50%
	Manual1, // 40%
	Manual2, // 70%
	Manual3, // 100%
};
typedef struct MachineStatus
{
	float temporature; // �µ� ����
	float humidity; // ���� ����
	float dust01Ratio; // PM 0.1���� ���� ��. �ټ� ����Ȯ
	float dust03Ratio; // PM 2.5���� ���� ��.
	float dust10Ratio; // PM 10 ���� ���� ��
	float averRatio; // ��� ��.
	int prorityIndex; // �ֿ켱���� �� ���� ��
	PlayMode playMode; // ���� ���
	//
	char* GetMode()
	{
		switch (playMode)
		{
		case PlayMode::Auto0:
			return "Auto 0";
			break;
		case PlayMode::Auto1:
			return "Auto 1";
			break;
		case PlayMode::Auto2:
			return "Auto 2";
			break;
		case PlayMode::Auto3:
			return "Auto 3";
			break;
		case PlayMode::Manual1:
			return "Manual 40%";
			break;
		case PlayMode::Manual2:
			return "Manual 70%";
			break;
		case PlayMode::Manual3:
			return "Manual 100%";
			break;
		default:
			break;
		}
	}
};

#endif // !_AC_STRUCTURE_HEADER_
